#include "sexComboDelegate.h"

sexComboDelegate::sexComboDelegate(QObject *parent) : QItemDelegate(parent)
{
}

sexComboDelegate::~sexComboDelegate(void)
{
}

QWidget *sexComboDelegate::createEditor(QWidget *parent,
										const QStyleOptionViewItem &/* option */,
										const QModelIndex &/* index */) const
{
	QComboBox *editor = new QComboBox(parent);
	editor->addItem("Female");
	editor->addItem("Male");
	return editor;
}

void sexComboDelegate::setEditorData(QWidget *editor,
									 const QModelIndex &index) const
{
	QComboBox *cmbBox = static_cast<QComboBox*>(editor);	
	cmbBox->setCurrentIndex(0);
}

void sexComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
									const QModelIndex &index) const
{
	QComboBox *cmbBox = static_cast<QComboBox*>(editor);
	model->setData(index, cmbBox->currentIndex());
}

void sexComboDelegate::updateEditorGeometry(QWidget *editor,
											const QStyleOptionViewItem &option,
											const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
