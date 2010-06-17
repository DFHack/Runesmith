#ifndef RUNESMITH_H
#define RUNESMITH_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include "DFInterface.H"
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
	void dwarfSelected(const QModelIndex& index);
	void creatureSelected(const QModelIndex& index);
	void writeChanges();
	void addTraitWrap();

private:
	void clean();

	Ui::RunesmithClass ui;
	progBarDelegate skillProgDele;
	progBarDelegate cSkillProgDele;
	sexComboDelegate sCD;
	traitsComboDelegate tCD;
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

	DFInterface *DFI;
};

#endif // RUNESMITH_H
