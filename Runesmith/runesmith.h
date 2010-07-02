#ifndef RUNESMITH_H
#define RUNESMITH_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include "DFInterface.h"
#include "ui_runesmith.h"
#include "dwarfTableModel.h"
#include "skillsTableModel.h"
#include "creatureTableModel.h"
#include "attrTableModel.h"
#include "progBarDelegate.h"
#include "labTableModel.h"
#include "flagTableModel.h"
#include "miscTableModel.h"
#include "traitsTableModel.h"
#include "sexComboDelegate.h"
#include "traitsComboDelegate.h"
#include "moodTableModel.h"
#include "moodComboDelegate.h"
#include "setMainRaceDialog.h"

class Runesmith : public QMainWindow
{
	Q_OBJECT

public:
	Runesmith(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~Runesmith();

public slots:
	void attach();
	void detatch();
	void forceResume();
	void close();
	void update();
	void aboutSlot();
	void showDead(bool state);
	void dwarfSelected(const QModelIndex& index, const QModelIndex&);
	void creatureSelected(const QModelIndex& index, const QModelIndex&);
	void writeChanges();
	void dAddTraitWrap();
	void cAddTraitWrap();
	void setRace();
	void setRaceAttrs();
	void setRaceSkills();

private:
	void clean();

	Ui::RunesmithClass ui;
	progBarDelegate skillProgDele;
	progBarDelegate cSkillProgDele;
	sexComboDelegate sCD;
	traitsComboDelegate tCD;
	moodComboDelegate mCD;
	QLabel connectLbl;

	dwarfTableModel *dTM;
	skillsTableModel *dsTM;
	creatureTableModel *cTM;
	skillsTableModel *csTM;
	attrTableModel *daTM;
	attrTableModel *caTM;
	labTableModel *dlTM;
	labTableModel *clTM;
	flagTableModel *dfTM;
	flagTableModel *cfTM;
	miscTableModel *dmTM;
	miscTableModel *cmTM;
	traitsTableModel *dtTM;
	traitsTableModel *ctTM;
	moodTableModel *dmooTM;

	DFInterface *DFI;
};

#endif // RUNESMITH_H
