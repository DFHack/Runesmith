 #include <QMessageBox>
#include "runesmith.h"
#include "rsException.h"
#include "about.h"

Runesmith::Runesmith(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), dTM(NULL), Creatures(NULL), Tran(NULL),
	attached(false), numCreatures(0)
{
	ui.setupUi(this);	
	
	if(!(dTM = new dwarfTableModel(this)))
			throw RSException();	
		
	QApplication::connect(ui.action_Connect, SIGNAL(triggered()), this, SLOT(attach()));
	QApplication::connect(ui.action_Disconnect, SIGNAL(triggered()), this, SLOT(detatch()));
	QApplication::connect(ui.action_Refresh, SIGNAL(triggered()), this, SLOT(update()));
	QApplication::connect(ui.actionE_xit, SIGNAL(triggered()), this, SLOT(close()));
	QApplication::connect(ui.action_About, SIGNAL(triggered()), this, SLOT(aboutSlot()));
	
	try
    {
		DF = new DFHack::API("Memory.xml");        
    }
	catch (std::exception& e)
    {
        throw;
    }

	attach();
}

Runesmith::~Runesmith()
{	
	detatch();
	if(dTM)
		delete dTM;
}

void Runesmith::close()
{
	QApplication::quit();
}

void Runesmith::attach()
{
	if(!attached)
	{
		try
		{
			DF->Attach();
		}
		catch(std::exception &e)
		{
			QMessageBox msgBox(
				QMessageBox::Critical, "Error!", e.what(), QMessageBox::Ok, this);			
			msgBox.exec();
			return;
		}

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
		dTM->update(numCreatures);ui.dwarvesTV->setModel(dTM);	
		attached = true;
		DF->Resume();
	}	
}

void Runesmith::detatch()
{
	if(attached)
	{
		DF->Suspend();
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

void Runesmith::update()
{
	if(attached)
	{
		DF->Suspend();
		dTM->update(numCreatures);ui.dwarvesTV->setModel(dTM);
		DF->Resume();
	}
}

void Runesmith::aboutSlot()
{
	About abDiaInstance;
	abDiaInstance.exec();
}
