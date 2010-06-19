#ifndef SETMAINRACE_H
#define SETMAINRACE_H

#include <QtGui/QMainWindow>
#include "ui_setMainRaceDialog.h"

class SetMainRaceDialog : public QDialog
{
	Q_OBJECT

public:
	SetMainRaceDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~SetMainRaceDialog(void);
	QString getRaceName();

private slots:
		void setRName();

private:
	Ui::setMainRaceDialog mrDia;
	QString rname;
};

#endif
