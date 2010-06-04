#ifndef RUNESMITH_H
#define RUNESMITH_H

#include <QtGui/QMainWindow>
#include <DFHack.h>
#include "ui_runesmith.h"
#include "dwarfTableModel.h"

class Runesmith : public QMainWindow
{
	Q_OBJECT

public:
	Runesmith(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Runesmith();

public slots:
	void attach();
	void detatch();
	void close();
	void update();
	void aboutSlot();

private:
	void suspend();
	void resume();

private:
	Ui::RunesmithClass ui;
	dwarfTableModel *dTM;
	DFHack::ContextManager *DFMgr;
    DFHack::Context *DF;
	DFHack::Materials *Materials;
	DFHack::Translation *Tran;
	DFHack::Creatures *Creatures;
	uint32_t numCreatures;
	bool attached;
};

#endif // RUNESMITH_H
