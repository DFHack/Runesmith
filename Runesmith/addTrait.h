#ifndef ADDTRAIT_H
#define ADDTRAIT_H

#include <QtGui/QMainWindow>
#include <map>
#include "ui_addTrait.h"
#include "DFInterface.h"

class addTrait : public QDialog
{
	Q_OBJECT

public:
	addTrait(QWidget *parent = 0, 
		Qt::WFlags flags = 0,
		DFHack::t_creature *creature = NULL,
		DFInterface *nDFI = NULL);
	~addTrait(void);
	int getIndex1();
	int getIndex2();

private slots:
	void populateLevel(int index);
	void addAction();

private:
	std::map<unsigned int, unsigned int> IDs;
	int index1;
	int index2;
	DFInterface *DFI;
	Ui::addTraitDia atD;
};

#endif