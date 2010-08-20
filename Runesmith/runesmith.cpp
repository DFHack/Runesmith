#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <DFHack.h>
#include <limits>
#include "runesmith.h"
#include "rsException.h"
#include "about.h"
#include "addTrait.h"
#include "addLabour.h"
#include "numInputDialog.h"
#include "exportDialog.h"

Runesmith::Runesmith(QWidget *parent, Qt::WFlags flags)
: QMainWindow(parent, flags), DFI(NULL)
{
	ui.setupUi(this);
	ui.skillsTV->setItemDelegateForColumn(2, &skillProgDele);
	ui.cSkillsTV->setItemDelegateForColumn(2, &cSkillProgDele);
	ui.dMiscTV->setItemDelegateForRow(3, &sCD);
	ui.cMiscTV->setItemDelegateForRow(3, &sCD);
	ui.dTraitsTV->setItemDelegate(&tCD);
	ui.cTraitsTV->setItemDelegate(&tCD);
	ui.dMoodTV->setItemDelegate(&mCD);

	if(!(dTM = new dwarfTableModel(this))) throw RSException();
	if(!(dsTM = new skillsTableModel(this))) throw RSException();
	if(!(cTM = new creatureTableModel(this))) throw RSException();
	if(!(csTM = new skillsTableModel(this))) throw RSException();
	if(!(daTM = new attrTableModel(this))) throw RSException();
	if(!(caTM = new attrTableModel(this))) throw RSException();
	if(!(dlTM = new labTableModel(this))) throw RSException();
	if(!(clTM = new labTableModel(this))) throw RSException();
	if(!(dfTM = new flagTableModel(this))) throw RSException();
	if(!(cfTM = new flagTableModel(this))) throw RSException();
	if(!(dmTM = new miscTableModel(this))) throw RSException();
	if(!(cmTM = new miscTableModel(this))) throw RSException();
	if(!(dtTM = new traitsTableModel(this))) throw RSException();
	if(!(ctTM = new traitsTableModel(this))) throw RSException();
	if(!(dmooTM = new moodTableModel(this))) throw RSException();

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
	ui.dMiscTV->setModel(dmTM);
	ui.cMiscTV->setModel(cmTM);
	ui.dTraitsTV->setModel(dtTM);
	ui.cTraitsTV->setModel(ctTM);
	ui.dMoodTV->setModel(dmooTM);

	//this wasn't working correctly in the designer...
	ui.skillsTV->horizontalHeader()->setResizeMode(dsTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cSkillsTV->horizontalHeader()->setResizeMode(csTM->getNumCols()-1, QHeaderView::Stretch);
	ui.dAttrTV->horizontalHeader()->setResizeMode(daTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cAttrTV->horizontalHeader()->setResizeMode(caTM->getNumCols()-1, QHeaderView::Stretch);	
	ui.dLabTV->horizontalHeader()->setResizeMode(dlTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cLabTV->horizontalHeader()->setResizeMode(clTM->getNumCols()-1, QHeaderView::Stretch);
	ui.dFlagTV->horizontalHeader()->setResizeMode(dfTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cFlagTV->horizontalHeader()->setResizeMode(cfTM->getNumCols()-1, QHeaderView::Stretch);
	ui.dMiscTV->horizontalHeader()->setResizeMode(dmTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cMiscTV->horizontalHeader()->setResizeMode(cmTM->getNumCols()-1, QHeaderView::Stretch);
	ui.dTraitsTV->horizontalHeader()->setResizeMode(dtTM->getNumCols()-1, QHeaderView::Stretch);
	ui.cTraitsTV->horizontalHeader()->setResizeMode(ctTM->getNumCols()-1, QHeaderView::Stretch);
	ui.dMoodTV->horizontalHeader()->setResizeMode(dmooTM->getNumCols()-1, QHeaderView::Stretch);

	try
	{
		DFI = new DFInterface();
		skillProgDele.setDFI(DFI);
		cSkillProgDele.setDFI(DFI);
		tCD.setDFI(DFI);
		mCD.setDFI(DFI);
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
	
	QApplication::connect(
		ui.dwarvesTV->selectionModel(),
		SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
		this,
		SLOT(dwarfSelected(const QModelIndex&, const QModelIndex&)));

	QApplication::connect(
		ui.creaturesTV->selectionModel(), 
		SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
		this,
		SLOT(creatureSelected(const QModelIndex&, const QModelIndex&)));

	QApplication::connect(ui.actionShow_Dead, SIGNAL(triggered(bool)), this, SLOT(showDead(bool)));
	QApplication::connect(ui.action_Write_Changes, SIGNAL(triggered()), this, SLOT(writeChanges()));
	QApplication::connect(ui.action_Force_Resume, SIGNAL(triggered()), this, SLOT(forceResume()));
	QApplication::connect(ui.dAddTraitBtn, SIGNAL(clicked()), this, SLOT(dAddTraitWrap()));
	QApplication::connect(ui.cAddTraitBtn, SIGNAL(clicked()), this, SLOT(cAddTraitWrap()));
	QApplication::connect(ui.dAddLabBtn, SIGNAL(clicked()), this, SLOT(dAddLabourWrap()));
	QApplication::connect(ui.cAddLabBtn, SIGNAL(clicked()), this, SLOT(cAddLabourWrap()));
	QApplication::connect(ui.action_Set_Main_Race, SIGNAL(triggered()), this, SLOT(setRace()));
	QApplication::connect(ui.actionSet_Dwarves_Attributes, SIGNAL(triggered()), this, SLOT(setRaceAttrs()));
	QApplication::connect(ui.actionSet_Dwarves_Skills, SIGNAL(triggered()), this, SLOT(setRaceSkills()));
	QApplication::connect(ui.action_Genocide, SIGNAL(triggered()), cTM, SLOT(genocide()));
	QApplication::connect(ui.action_Export_All_Dwarves, SIGNAL(triggered()), this, SLOT(exportAllDwarves()));
	QApplication::connect(ui.dRemoveBtn, SIGNAL(clicked()), this, SLOT(dRemoveLabour()));
	QApplication::connect(ui.cRemoveBtn, SIGNAL(clicked()), this, SLOT(cRemoveLabour()));
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
	if(dmTM) delete dmTM;
	if(cmTM) delete cmTM;
	if(dtTM) delete dtTM;
	if(ctTM) delete ctTM;
	if(dmooTM) delete dmooTM;
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
			tCD.setDFI(DFI);
			mCD.setDFI(DFI);
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
		connectLbl.setText("Disconnected");
		return;
	}
	
	connectLbl.setText("Connected to " + DFI->getVersion());
	ui.statusBar->addPermanentWidget(&connectLbl);
	dTM->update(DFI);
	cTM->update(DFI);	
}

void Runesmith::detatch()
{
	DFI->detatch();
	dTM->update(DFI);
	cTM->update(DFI);
	tCD.setDFI(NULL);
	tCD.setDFI(NULL);
	clean();
	connectLbl.setText("Disconnected");
}

void Runesmith::forceResume()
{
	try
	{
		DFI->forceResume();
	}
	catch(std::exception &e)
	{
		QString temp(e.what()[0]);
		temp = temp.toUpper();
		temp.append(e.what()+1);		
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", temp, QMessageBox::Ok, this);			
		msgBox.exec();
	}
}

void Runesmith::update()
{
	if(DFI->changesPending())
	{
		QMessageBox msgBox(QMessageBox::Warning,
			"Warning!",
			"Would you like to write pending changes first?",
			QMessageBox::Yes | QMessageBox::No, this);

		if(msgBox.exec() == QMessageBox::Yes)
			writeChanges();
	}

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

void Runesmith::dwarfSelected(const QModelIndex& index, const QModelIndex&)
{
	RSCreature* dwarf = DFI->getDwarf(index.row());
	dsTM->setCreature(DFI, dwarf);
	daTM->setCreature(DFI, dwarf);
	dlTM->setCreature(dwarf);
	dfTM->setCreature(DFI, dwarf);
	dmTM->setCreature(DFI, dwarf);
	dtTM->setCreature(dwarf);
	dmooTM->setCreature(DFI, dwarf);
	skillProgDele.setCreature(dwarf);
	mCD.setCreature(dwarf);
}

void Runesmith::creatureSelected(const QModelIndex& index, const QModelIndex&)
{
	RSCreature* creature = DFI->getCreature(index.row());
	cTM->setCurrent(creature);
	csTM->setCreature(DFI, creature);
	caTM->setCreature(DFI, creature);
	clTM->setCreature(creature);
	cfTM->setCreature(DFI, creature);
	cmTM->setCreature(DFI, creature);
	ctTM->setCreature(creature);
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
	dmTM->clear();
	cmTM->clear();
	dtTM->clear();
	ctTM->clear();
	dmooTM->clear();
}

void Runesmith::showDead(bool state)
{
	DFI->setProcessDead(state);
}

void Runesmith::writeChanges()
{
	if(!DFI->writeAllChanges())
	{
		clean();
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", "Could not write changes!\n" 
			"Changes will be kept until successfully written or "
			"'No' is selected when asked to write changes before 'Refreshing'",
			QMessageBox::Ok, this);			
		msgBox.exec();
		return;
	}

	dTM->update(DFI);
	cTM->update(DFI);
	clean();
}

void Runesmith::dAddTraitWrap()
{
	addTrait temp(this, 0, dtTM->getCreature(), DFI);
	temp.setModal(true);
	temp.exec();

	if(!dtTM->addTrait(temp.getIndex1(), temp.getIndex2()))
	{
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", "Could not add trait!",
			QMessageBox::Ok, this);			
		msgBox.exec();
	}
}

void Runesmith::cAddTraitWrap()
{
	addTrait temp(this, 0, ctTM->getCreature(), DFI);
	temp.setModal(true);
	temp.exec();

	if(!ctTM->addTrait(temp.getIndex1(), temp.getIndex2()))
	{
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", "Could not add trait!",
			QMessageBox::Ok, this);			
		msgBox.exec();
	}
}

void Runesmith::dAddLabourWrap()
{
	addLabour temp(this, 0, dtTM->getCreature(), DFI);
	temp.setModal(true);
	temp.exec();

	if(!dlTM->addLabour(temp.getIndex()))
	{
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", "Could not add Labour!",
			QMessageBox::Ok, this);			
		msgBox.exec();
	}
}

void Runesmith::cAddLabourWrap()
{
	addLabour temp(this, 0, ctTM->getCreature(), DFI);
	temp.setModal(true);
	temp.exec();

	if(!clTM->addLabour(temp.getIndex()))
	{
		QMessageBox msgBox(QMessageBox::Critical,
			"Error!", "Could not add Labour!",
			QMessageBox::Ok, this);			
		msgBox.exec();
	}
}


void Runesmith::dRemoveLabour()
{
	QModelIndexList indexes = ui.dLabTV->selectionModel()->selection().indexes();
	dlTM->removeLabours(indexes);
}

void Runesmith::cRemoveLabour()
{
	QModelIndexList indexes = ui.cLabTV->selectionModel()->selection().indexes();
	clTM->removeLabours(indexes);
}

void Runesmith::setRace()
{
	SetMainRaceDialog temp;
	temp.setModal(true);
	temp.exec();
	QString tString = temp.getRaceName();
	DFI->setMainRace(tString);
	ui.tabWidget->setTabText(0, tString);
	update();
}

void Runesmith::setRaceSkills()
{
	NumInputDialog temp;
	temp.setModal(true);
	temp.exec();
	unsigned int val = temp.getInputVal();

	if(val > std::numeric_limits<uint8_t>::max())
		val = std::numeric_limits<uint8_t>::max();

	DFI->setAllRaceSkills(val);
}

void Runesmith::setRaceAttrs()
{
	NumInputDialog temp;
	temp.setModal(true);
	temp.exec();
	unsigned int val = temp.getInputVal();

	if(val > std::numeric_limits<uint16_t>::max())
		val = std::numeric_limits<uint16_t>::max();

	DFI->setAllRaceAttrs(val);
}

void Runesmith::exportAllDwarves()
{
	ExportDialog temp;
	temp.exec();

	QString filename = QFileDialog::getSaveFileName(this,
		tr("Save To..."),
		"./Dwarves", 
		"XML (*.xml);;Comma Seperated Values (*.csv)");

	if(!filename.isEmpty())
		DFI->exportAllDwarves(filename, temp.getFlags());
}