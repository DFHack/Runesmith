#include "ExportDialog.h"

ExportDialog::ExportDialog(QWidget *parent, Qt::WFlags flags)
{
	exDia.setupUi(this);
	QApplication::connect(exDia.exportBtn, SIGNAL(clicked()), this, SLOT(setFlags()));
}

ExportDialog::~ExportDialog(void)
{
}

void ExportDialog::setFlags()
{
	flags = 0;
	
	if(exDia.raceCB)
		flags |= RACE;
	//this->close();
}

unsigned int ExportDialog::getFlags()
{
	return flags;
}