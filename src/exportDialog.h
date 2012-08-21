#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QtGui/QMainWindow>
#include "ui_export.h"
#include "ExportableStats.h"

class ExportDialog : public QDialog
{
	Q_OBJECT

public:
	ExportDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ExportDialog(void);
	unsigned int getFlags();

private slots:
		void setFlags();

private:
	Ui::exportDia exDia;
	unsigned int flags;
};

#endif
