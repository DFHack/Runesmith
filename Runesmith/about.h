#ifndef ABOUT_H
#define ABOUT_H

#include <QtGui/QMainWindow>
#include "ui_about.h"

class About : public QDialog
{
	Q_OBJECT

public:
	About(QWidget *parent = 0, Qt::WFlags flags = 0);
	~About(void);

private:
	Ui::aboutDialog abDia;
};

#endif
