#include "moodComboDelegate.h"
#include "traitsTableModel.h"

moodComboDelegate::moodComboDelegate(QObject *parent) 
: QItemDelegate(parent), creature(NULL), DFI(NULL)
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
	
	if(index.row() == 0)
	{
		editor->addItem("None");
		editor->addItem("Fey");
		editor->addItem("Secretive");
		editor->addItem("Possesed");
		editor->addItem("Macabre");
		editor->addItem("Fell");
		editor->addItem("Melancholy");
	}
	else if(index.row() == 1)
	{
		if(DFI && creature)
		{
			for(int i=0; i<creature->defaultSoul.numSkills; i++)
			{
				editor->addItem(DFI->translateSkill(creature->defaultSoul.skills[i].id));
			}
		}
	}
	/*else
	{
		if(DFI && creature)
		{
			std::vector<DFHack::t_matgloss> const& organic = DFI->getOrganicMats();
			std::vector<DFHack::t_matgloss> const& inorganic = DFI->getInorgaincMats();
			std::vector<DFHack::t_material> &mats = DFI->getMoodMats(creature->id);

			QString type = DFI->getMaterialType(mats[index.row()-2]);
			
			if(type == "organic")
			{
				for(int i=0; i<organic.size(); i++)
				{
					editor->addItem(organic[i].id);
				}
			}
			else if(type == "inorganic")
			{
				for(int i=0; i<inorganic.size(); i++)
				{
					editor->addItem(inorganic[i].id);
				}
			}
			else if(type == "any")
			{
				for(int i=0; i<inorganic.size(); i++)
				{
					editor->addItem(inorganic[i].id);
				}

				for(int i=0; i<organic.size(); i++)
				{
					editor->addItem(organic[i].id);
				}
			}
			else
			{
			}
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
