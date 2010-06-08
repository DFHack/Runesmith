#ifndef RUNESMITH_H
#define RUNESMITH_H

#include <QtGui/QMainWindow>
#include "DFInterface.H"
#include "ui_runesmith.h"
#include "dwarfTableModel.h"
#include "skillsTableModel.h"
#include "creatureTableModel.h"
#include "attrTableModel.h"

class Runesmith : public QMainWindow
{
	Q_OBJECT

public:
	Runesmith(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~Runesmith();

public slots:
	void attach();
	void detatch();
	void close();
	void update();
	void aboutSlot();
	void dwarfSelected(const QModelIndex& index);
	void creatureSelected(const QModelIndex& index);

private:
	void clean();

	Ui::RunesmithClass ui;

	dwarfTableModel *dTM;
	skillsTableModel *dsTM;
	creatureTableModel *cTM;
	skillsTableModel *csTM;
	attrTableModel *daTM;
	attrTableModel *caTM;

	DFInterface *DFI;
};

#endif // RUNESMITH_H
