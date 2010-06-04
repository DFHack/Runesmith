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
	QApplication::connect(ui.dwarvesTV, SIGNAL(clicked(const QModelIndex&)), dTM, SLOT(selected(const QModelIndex&)));
	
	try
    {
		DFMgr = new DFHack::ContextManager("Memory.xml");
		DF = DFMgr->getSingleContext();       
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

	if(DFMgr)
		delete DFMgr;
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
		suspend();	
		dTM->attach(DF);
		dTM->update(numCreatures);
		ui.dwarvesTV->setModel(dTM);	
		attached = true;
		resume();
	}	
}

void Runesmith::detatch()
{
	if(attached)
	{
		dTM->detatch();
		suspend();
		DF->Detach();
		attached = false;
		numCreatures = 0;
	}
}

void Runesmith::update()
{
	if(attached)
	{
		suspend();
		dTM->update(numCreatures);
		//ui.dwarvesTV->setModel(dTM);
		resume();
	}
}

void Runesmith::aboutSlot()
{
	About abDiaInstance;
	abDiaInstance.exec();
}

void Runesmith::suspend()
{
	DF->Suspend();	
	Materials->ReadAllMaterials();

	if(!Creatures->Start(numCreatures))
		throw RSException();    

	if(!numCreatures)
		throw RSException();

	if(!Tran->Start())
		throw RSException();
}

void Runesmith::resume()
{
	//if(Tran)
	//	Tran->Finish();
	if(Creatures)
		Creatures->Finish();

	DF->Resume();		
}