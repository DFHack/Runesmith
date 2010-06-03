#include "runesmith.h"
#include "rsException.h"

Runesmith::Runesmith(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), dTM(NULL), Creatures(NULL), Tran(NULL),
	attached(false), numCreatures(0)
{
	ui.setupUi(this);	
	QApplication::connect(ui.action_Connect, SIGNAL(triggered()), this, SLOT(attach()));
	QApplication::connect(ui.action_Disconnect, SIGNAL(triggered()), this, SLOT(detatch()));
	QApplication::connect(ui.action_Refresh, SIGNAL(triggered()), dTM, SLOT(update(numCreatures)));
	QApplication::connect(ui.actionE_xit, SIGNAL(triggered()), this, SLOT(close()));
	
	if(!(dTM = new dwarfTableModel(this)))
			throw RSException();

	try
    {
		DF = new DFHack::API("Memory.xml");        
    }
	catch (std::exception& e)
    {
        throw;
    }		
}

Runesmith::~Runesmith()
{
	if(dTM)
		delete dTM;
	detatch();
}

void Runesmith::close()
{
	QApplication::quit();
}

void Runesmith::attach()
{
	if(!attached)
	{
		DF->Attach();
		Creatures = DF->getCreatures();
		Materials = DF->getMaterials();
		Tran = DF->getTranslation();
		Materials->ReadAllMaterials();

		if(!Creatures->Start(numCreatures))
			throw RSException();    

		if(!numCreatures)
			throw RSException();

		if(!Tran->Start())
			throw RSException();		

		dTM->attach(DF);
		dTM->update(numCreatures);
		ui.dwarvesTV->setModel(dTM);
		attached = true;		
	}	
}

void Runesmith::detatch()
{
	if(attached)
	{
		dTM->detatch();

		if(Creatures)
			Creatures->Finish();

		if(Tran)
			Tran->Finish();

		DF->Detach();
		attached = false;
		numCreatures = 0;
	}
}
