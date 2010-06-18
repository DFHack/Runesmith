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
	
	editor->addItem("None");
	editor->addItem("Fey");
	editor->addItem("Secretive");
	editor->addItem("Possesed");
	editor->addItem("Macabre");
	editor->addItem("Fell");
	editor->addItem("Melancholy");

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