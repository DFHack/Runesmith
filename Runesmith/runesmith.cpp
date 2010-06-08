#include <QMessageBox>
#include <QFile>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include <DFHack.h>
#include "runesmith.h"
#include "rsException.h"
#include "about.h"
#include "progBarDelegate.h"
#include "levelParse.h"

Runesmith::Runesmith(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags), dTM(NULL), Creatures(NULL), Tran(NULL),
numCreatures(0), DF(NULL), DFMgr(NULL)
{
	ui.setupUi(this);	
	//progBarDelegate *tempdeli = new progBarDelegate(this);
	//ui.dwarvesTV->setItemDelegateForColumn(2, tempdeli);

	/*
	QFile xmlFile("experience.xml");
	QXmlInputSource source(&xmlFile);
	levelParse handler; 
	QXmlSimpleReader reader;
	reader.setContentHandler(&handler);
	reader.parse(source);
	*/

	if(!(dTM = new dwarfTableModel(this)))
		throw RSException();

	if(!(sTM = new skillsTableModel(this)))
		throw RSException();

	if(!(cTM = new creatureTableModel(this)))
		throw RSException();

	if(!(csTM = new skillsTableModel(this)))
		throw RSException();

	ui.dwarvesTV->setModel(dTM);		
	ui.skillsTV->setModel(sTM);
	ui.creaturesTV->setModel(cTM);
	ui.cSkillsTV->setModel(csTM);

	QApplication::connect(ui.action_Connect, SIGNAL(triggered()), this, SLOT(attach()));
	QApplication::connect(ui.action_Disconnect, SIGNAL(triggered()), this,
		SLOT(detatch()));
	QApplication::connect(ui.action_Refresh, SIGNAL(triggered()), this, SLOT(update()));
	QApplication::connect(ui.actionE_xit, SIGNAL(triggered()), this, SLOT(close()));
	QApplication::connect(ui.action_About, SIGNAL(triggered()), this, SLOT(aboutSlot()));
	QApplication::connect(ui.dwarvesTV, SIGNAL(clicked(const QModelIndex&)), this,
		SLOT(dwarfSelected(const QModelIndex&)));
	QApplication::connect(ui.creaturesTV, SIGNAL(clicked(const QModelIndex&)), this,
		SLOT(creatureSelected(const QModelIndex&)));

	try
	{
		DFMgr = new DFHack::ContextManager("Memory.xml");
		attach();   
	}
	catch (std::exception& e)
	{
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", e.what(), QMessageBox::Ok, this);			
		msgBox.exec();
	}	
}

Runesmith::~Runesmith()
{	
	detatch();
	if(dTM)
		delete dTM;

	if(sTM)
		delete sTM;

	if(cTM)
		delete cTM;

	if(DFMgr)
		delete DFMgr;
}

void Runesmith::close()
{
	QApplication::quit();
}

void Runesmith::attach()
{
	if(!DF)
	{
		try
		{
			DF = DFMgr->getSingleContext(); 
		}
		catch (std::exception& e)
		{
			QMessageBox msgBox(QMessageBox::Critical,
				"Error!", e.what(), QMessageBox::Ok, this);			
			msgBox.exec();
			return;
		}
	}

	if(DF)
	{
		if(isContextValid())
		{

			try
			{
				DF->Attach();
			}
			catch (std::exception& e)
			{
				QMessageBox msgBox(QMessageBox::Critical,
					"Error!", e.what(), QMessageBox::Ok, this);			
				msgBox.exec();
			}	

			Creatures = DF->getCreatures();
			Materials = DF->getMaterials();
			Tran = DF->getTranslation();
			suspend();	
			dTM->attach(DF);
			cTM->attach(DF);
			dTM->update(numCreatures);	
			cTM->update(numCreatures);
			resume();
		}
	}	
}

void Runesmith::detatch()
{
	if(DF)
	{
		if(isContextValid())
		{
			if(DF->isAttached())
			{
				dTM->detatch();
				cTM->detatch();
				suspend();
				DF->Detach();
				numCreatures = 0;
			}
		}
	}
}

void Runesmith::update()
{
	if(DF)
	{
		if(isContextValid())
		{
			if(DF->isAttached())
			{
				suspend();
				dTM->update(numCreatures);
				cTM->update(numCreatures);
				resume();
				return;
			}
		}
	}

	dTM->detatch();
	cTM->detatch();
}

void Runesmith::aboutSlot()
{
	About abDiaInstance;
	abDiaInstance.exec();
}

void Runesmith::suspend()
{
	if(Tran)
		Tran->Finish();

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
	if(Creatures)
		Creatures->Finish();

	DF->Resume();		
}

void Runesmith::dwarfSelected(const QModelIndex& index)
{
	sTM->setCreature(DF,dTM->getCreatureP(index.row()));
}

void Runesmith::creatureSelected(const QModelIndex& index)
{
	csTM->setCreature(DF,cTM->getCreatureP(index.row()));	
}

bool Runesmith::isContextValid()
{
	DFHack::BadContexts inval;
	DFMgr->Refresh(&inval);
	return !inval.Contains(DF);
}
