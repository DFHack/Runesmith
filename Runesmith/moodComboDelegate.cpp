#include "moodComboDelegate.h"
#include "traitsTableModel.h"

moodComboDelegate::moodComboDelegate(QObject *parent) 
: QItemDelegate(parent)
{
}

moodComboDelegate::~moodComboDelegate(void)
{
}

QWidget *moodComboDelegate::createEditor(QWidget *parent,
										   const QStyleOptionViewItem &/* option */,
										   const QModelIndex &index) const
{
	QComboBox *editor = new QComboBox(parent);
	
	if(index.row() == 1)
	{
	editor->addItem("None");
	editor->addItem("Fey");
	editor->addItem("Secretive");
	editor->addItem("Possesed");
	editor->addItem("Macabre");
	editor->addItem("Fell");
	editor->addItem("Melancholy");
	}
	/*else
	{
		if(DFI && creature)
		{
			std::vector<DFHack::t_matgloss> const& organic = DFI->getOrganicMats();
			std::vector<DFHack::t_matgloss> const& inorganic = DFI->getInorgaincMats();
			std::vector<DFHack::t_material> &mats = DFI->getMoodMats(creature->id);

			if(mats[index.row()-2].
		}
	}*/

	return editor;
}

void moodComboDelegate::setEditorData(QWidget *editor,
										const QModelIndex &index) const
{
	QComboBox *cmbBox = static_cast<QComboBox*>(editor);	
	cmbBox->setCurrentIndex(0);
}

void moodComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
									   const QModelIndex &index) const
{
	QComboBox *cmbBox = static_cast<QComboBox*>(editor);
	model->setData(index, cmbBox->currentIndex());
}

void moodComboDelegate::updateEditorGeometry(QWidget *editor,
											   const QStyleOptionViewItem &option,
											   const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

void moodComboDelegate::setDFI(DFInterface *nDFI)
{
	DFI = nDFI;
}

void moodComboDelegate::setCreature(DFHack::t_creature *nCreature)
{
	if(nCreature)
		creature = nCreature;
	else	
		creature = NULL;
}
