#ifndef ADDLABOUR_H
#define ADDLABOUR_H

#include <QtGui/QMainWindow>
#include <map>
#include "ui_addLabour.h"
#include "DFInterface.h"

class addLabour : public QDialog
{
	Q_OBJECT

public:
	addLabour(QWidget *parent = 0, 
		Qt::WFlags flags = 0,
		RSCreature* creature = NULL,
		DFInterface *nDFI = NULL);
	~addLabour(void);
	int getIndex();

private slots:
	void storeChoice();

private:
	std::map<unsigned int, unsigned int> IDs;
	int index;
	DFInterface *DFI;
	Ui::addLabDia labDia;
};

#endif