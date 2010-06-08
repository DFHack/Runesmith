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
: QMainWindow(parent, flags), dTM(NULL), DFI(NULL)
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

	try
	{
		DFI = new DFInterface();  
	}
	catch (std::exception& e)
	{
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", e.what(), QMessageBox::Ok, this);			
		msgBox.exec();
	}

	attach();

	QApplication::connect(ui.action_Connect, SIGNAL(triggered()), this, SLOT(attach()));
	QApplication::connect(ui.action_Disconnect, SIGNAL(triggered()), this, SLOT(detatch()));
	QApplication::connect(ui.action_Refresh, SIGNAL(triggered()), this, SLOT(update()));
	QApplication::connect(ui.actionE_xit, SIGNAL(triggered()), this, SLOT(close()));
	QApplication::connect(ui.action_About, SIGNAL(triggered()), this, SLOT(aboutSlot()));
	QApplication::connect(ui.dwarvesTV, SIGNAL(clicked(const QModelIndex&)), this,
		SLOT(dwarfSelected(const QModelIndex&)));
	QApplication::connect(ui.creaturesTV, SIGNAL(clicked(const QModelIndex&)), this,
		SLOT(creatureSelected(const QModelIndex&)));
}

Runesmith::~Runesmith()
{	
	if(dTM)
		delete dTM;

	if(sTM)
		delete sTM;

	if(cTM)
		delete cTM;

	if(DFI)
		delete DFI;
}

void Runesmith::close()
{
	QApplication::quit();
}

void Runesmith::attach()
{
	try
	{
		if(!DFI)
			DFI = new DFInterface();
		DFI->attach();
	}
	catch(std::exception &e)
	{
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", e.what(), QMessageBox::Ok, this);			
		msgBox.exec();
		return;
	}

	dTM->update(DFI);
	cTM->update(DFI);	
}

void Runesmith::detatch()
{
	DFI->detatch();
	dTM->update(DFI);
	cTM->update(DFI);
	sTM->clear();
}

void Runesmith::update()
{
	DFI->update();
	dTM->update(DFI);
	cTM->update(DFI);				
}

void Runesmith::aboutSlot()
{
	About abDiaInstance;
	abDiaInstance.exec();
}

void Runesmith::dwarfSelected(const QModelIndex& index)
{
	sTM->setCreature(DFI, DFI->getDwarf(index.row()));
}
