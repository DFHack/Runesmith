#ifndef RUNESMITH_H
#define RUNESMITH_H

#include <QtGui/QMainWindow>
#include <integers.h>
#include <DFGlobal.h>
#include <DFTypes.h>
#include <DFHackAPI.h>
#include <modules/Materials.h>
#include <modules/Creatures.h>
#include <modules/Translation.h>
#include "ui_runesmith.h"
#include "dwarfTableModel.h"

class Runesmith : public QMainWindow
{
	Q_OBJECT

public:
	Runesmith(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Runesmith();

private:
	Ui::RunesmithClass ui;
	dwarfTableModel *dTM;
	DFHack::API *DF;
	DFHack::Materials *Materials;
	DFHack::Translation *Tran;
	DFHack::Creatures *Creatures;
	uint32_t numCreatures;	
};

#endif // RUNESMITH_H
