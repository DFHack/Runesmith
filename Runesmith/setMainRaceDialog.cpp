#include "SetMainRaceDialog.h"

SetMainRaceDialog::SetMainRaceDialog(QWidget *parent, Qt::WFlags flags)
{
	mrDia.setupUi(this);
	QApplication::connect(mrDia.okButton, SIGNAL(clicked()), this, SLOT(setRName()));
}

SetMainRaceDialog::~SetMainRaceDialog(void)
{
}

void SetMainRaceDialog::setRName()
{
	rname = mrDia.mainRaceTxt->text();
	this->close();
}

QString SetMainRaceDialog::getRaceName()
{
	return rname;
}