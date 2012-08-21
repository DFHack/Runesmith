#ifndef NUMINPUTDIALOG_H
#define NUMINPUTDIALOG_H

#include <QtGui/QMainWindow>
#include "ui_numInput.h"

class NumInputDialog : public QDialog
{
	Q_OBJECT

public:
	NumInputDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~NumInputDialog(void);
	unsigned int getInputVal();

private slots:
		void setIV();

private:
	Ui::numInputDialog niDia;
	unsigned int inputVal;
};

#endif
