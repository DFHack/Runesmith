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
	ui.cSkillsTV->setItemDelegateForColumn(2, &cSkillProgDele);

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

	if(!(dlTM = new labTableModel(this)))
		throw RSException();

	if(!(clTM = new labTableModel(this)))
		throw RSException();

	if(!(dfTM = new flagTableModel(this)))
		throw RSException();

	if(!(cfTM = new flagTableModel(this)))
		throw RSException();

	ui.dwarvesTV->setModel(dTM);		
	ui.skillsTV->setModel(dsTM);
	ui.creaturesTV->setModel(cTM);
	ui.cSkillsTV->setModel(csTM);
	ui.cAttrTV->setModel(caTM);
	ui.dAttrTV->setModel(daTM);
	ui.dLabTV->setModel(dlTM);
	ui.cLabTV->setModel(clTM);
	ui.dFlagTV->setModel(dfTM);
	ui.cFlagTV->setModel(cfTM);
	//this wasn't working correctly in the designer...
	ui.skillsTV->horizontalHeader()->setResizeMode(dsTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cSkillsTV->horizontalHeader()->setResizeMode(csTM->getNumCols()-1, QHeaderView::Stretch);
	ui.dAttrTV->horizontalHeader()->setResizeMode(daTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cAttrTV->horizontalHeader()->setResizeMode(caTM->getNumCols()-1, QHeaderView::Stretch);	
	ui.dLabTV->horizontalHeader()->setResizeMode(dlTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cLabTV->horizontalHeader()->setResizeMode(clTM->getNumCols()-1, QHeaderView::Stretch);
	ui.dFlagTV->horizontalHeader()->setResizeMode(dfTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cFlagTV->horizontalHeader()->setResizeMode(cfTM->getNumCols()-1, QHeaderView::Stretch);

	try
	{
		DFI = new DFInterface();
		skillProgDele.setDFI(DFI);
		cSkillProgDele.setDFI(DFI);
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
	QApplication::connect(ui.actionShow_Dead, SIGNAL(triggered(bool)), this, SLOT(showDead(bool)));
}

Runesmith::~Runesmith()
{	
	if(dTM) delete dTM;
	if(dsTM) delete dsTM;
	if(cTM) delete cTM;
	if(csTM) delete csTM;
	if(daTM) delete daTM;
	if(caTM) delete caTM;
	if(dlTM) delete dlTM;
	if(clTM) delete clTM;
	if(dfTM) delete dfTM;
	if(cfTM) delete cfTM;
	if(DFI) delete DFI;
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
		{
			DFI = new DFInterface();
			skillProgDele.setDFI(DFI);
			cSkillProgDele.setDFI(DFI);
		}
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
	
	temp.setText("Connected to " + DFI->getVersion());
	ui.statusBar->addPermanentWidget(&temp);
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
	DFHack::t_creature *dwarf = DFI->getDwarf(index.row());
	dsTM->setCreature(DFI, dwarf);
	daTM->setCreature(DFI, dwarf);
	dlTM->setCreature(DFI, dwarf);
	dfTM->setCreature(DFI, dwarf);
	skillProgDele.setCreature(dwarf);
}

void Runesmith::creatureSelected(const QModelIndex& index)
{
	DFHack::t_creature *creature = DFI->getCreature(index.row());
	csTM->setCreature(DFI, creature);
	caTM->setCreature(DFI, creature);
	clTM->setCreature(DFI, creature);
	cfTM->setCreature(DFI, creature);
	cSkillProgDele.setCreature(creature);
}

void Runesmith::clean()
{
	dsTM->clear();
	csTM->clear();
	daTM->clear();
	caTM->clear();
	dlTM->clear();
	clTM->clear();
	dfTM->clear();
	cfTM->clear();
}

void Runesmith::showDead(bool state)
{
	DFI->setProcessDead(state);
}
