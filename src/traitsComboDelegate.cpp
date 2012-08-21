#include "traitsComboDelegate.h"
#include "traitsTableModel.h"

traitsComboDelegate::traitsComboDelegate(QObject *parent) 
: QItemDelegate(parent), DFI(NULL)
{
}

traitsComboDelegate::~traitsComboDelegate(void)
{
}

QWidget *traitsComboDelegate::createEditor(QWidget *parent,
										   const QStyleOptionViewItem &/* option */,
										   const QModelIndex &index) const
{
	QComboBox *editor = new QComboBox(parent);
	traitsTableModel *tbm = (traitsTableModel*)(index.model());
	unsigned int id = tbm->getTraitIndex(index.row());

	if(DFI)
	{
		std::vector< std::vector<std::string> > const& traits = DFI->getAllTraits();
		
		for(int j=0; j<traits[id].size()-1; j++)
		{
			editor->addItem(traits[id][j].c_str());
		}		
	}

	return editor;
}

void traitsComboDelegate::setEditorData(QWidget *editor,
										const QModelIndex &index) const
{
	QComboBox *cmbBox = static_cast<QComboBox*>(editor);	
	cmbBox->setCurrentIndex(0);
}

void traitsComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
									   const QModelIndex &index) const
{
	QComboBox *cmbBox = static_cast<QComboBox*>(editor);
	model->setData(index, cmbBox->currentIndex());
}

void traitsComboDelegate::updateEditorGeometry(QWidget *editor,
											   const QStyleOptionViewItem &option,
											   const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}

void traitsComboDelegate::setDFI(DFInterface *nDFI)
{
	DFI = nDFI;
}
