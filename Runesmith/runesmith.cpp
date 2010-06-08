#include <QMessageBox>
#include <QFile>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include <DFHack.h>
#include "runesmith.h"
#include "rsException.h"
#include "about.h"

Runesmith::Runesmith(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags), DFI(NULL)
{
	ui.setupUi(this);
	ui.skillsTV->setItemDelegateForColumn(2, &skillProgDele);	

	if(!(dTM = new dwarfTableModel(this)))
		throw RSException();

	if(!(dsTM = new skillsTableModel(this)))
		throw RSException();

	if(!(cTM = new creatureTableModel(this)))
		throw RSException();

	if(!(csTM = new skillsTableModel(this)))
		throw RSException();

	if(!(daTM = new attrTableModel(this)))
		throw RSException();

	if(!(caTM = new attrTableModel(this)))
		throw RSException();

	ui.dwarvesTV->setModel(dTM);		
	ui.skillsTV->setModel(dsTM);
	ui.creaturesTV->setModel(cTM);
	ui.cSkillsTV->setModel(csTM);
	ui.cAttrTV->setModel(caTM);
	ui.dAttrTV->setModel(daTM);

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

	if(dsTM)
		delete dsTM;

	if(cTM)
		delete cTM;

	if(csTM)
		delete csTM;

	if(daTM)
		delete daTM;

	if(caTM)
		delete caTM;

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
		QString temp(e.what()[0]);
		temp = temp.toUpper();
		temp.append(e.what()+1);		
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", temp, QMessageBox::Ok, this);			
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
	clean();
}

void Runesmith::update()
{
	DFI->update();
	dTM->update(DFI);
	cTM->update(DFI);	
	clean();
}

void Runesmith::aboutSlot()
{
	About abDiaInstance;
	abDiaInstance.exec();
}

void Runesmith::dwarfSelected(const QModelIndex& index)
{
	dsTM->setCreature(DFI, DFI->getDwarf(index.row()));
	daTM->setCreature(DFI, DFI->getDwarf(index.row()));
}

void Runesmith::creatureSelected(const QModelIndex& index)
{
	csTM->setCreature(DFI, DFI->getCreature(index.row()));
	caTM->setCreature(DFI, DFI->getCreature(index.row()));
}

void Runesmith::clean()
{
	dsTM->clear();
	csTM->clear();
	daTM->clear();
	caTM->clear();
}
