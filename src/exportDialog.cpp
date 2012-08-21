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

	if(exDia.nameCB)
		flags |= NAME;

	if(exDia.profCB)
		flags |= PROFESSION;

	if(exDia.happCB)
		flags |= HAPPINESS;

	if(exDia.skillsCB)
		flags |= SKILLS;
	
	if(exDia.attrCB)
		flags |= ATTRIBUTES;

	if(exDia.traitCB)
		flags |= TRAITS;

	if(exDia.labsCB)
		flags |= LABOURS;

	if(exDia.moodCB)
		flags |= MOOD;

	if(exDia.nickCB)
		flags |= NICKNAME;

	if(exDia.engCB)
		flags |= ENGLISH_NAME;

	if(exDia.sexCB)
		flags |= SEX;

	if(exDia.dobCB)
		flags |= DOB;

	if(exDia.ageCB)
		flags |= AGE;

	if(exDia.cProfCB)
		flags |= CUSTOM_PROF;
}

unsigned int ExportDialog::getFlags()
{
	return flags;
}