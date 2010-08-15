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
	flags = NONE;
	
	if(exDia.raceCB)
		flags = (ExportableStats)(flags | RACE);
	//this->close();
}

ExportableStats ExportDialog::getFlags()
{
	return flags;
}