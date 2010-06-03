#ifndef RUNESMITH_H
#define RUNESMITH_H

#include <QtGui/QMainWindow>
#include "ui_runesmith.h"

class Runesmith : public QMainWindow
{
	Q_OBJECT

public:
	Runesmith(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Runesmith();

private:
	Ui::RunesmithClass ui;
};

#endif // RUNESMITH_H
