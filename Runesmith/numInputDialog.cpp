#include "NumInputDialog.h"

NumInputDialog::NumInputDialog(QWidget *parent, Qt::WFlags flags)
{
	niDia.setupUi(this);
	QApplication::connect(niDia.okButton, SIGNAL(clicked()), this, SLOT(setIV()));
}

NumInputDialog::~NumInputDialog(void)
{
}

void NumInputDialog::setIV()
{
	inputVal = niDia.inpValTxt->text().toUInt();
	//this->close();
}

unsigned int NumInputDialog::getInputVal()
{
	return inputVal;
}