#ifndef SEXCOMBODELEGATE_H
#define SEXCOMBODELEGATE_H

 #include <QItemDelegate>
 #include <QModelIndex>
 #include <QObject>
 #include <QSize>
 #include <QComboBox>

class sexComboDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	sexComboDelegate(QObject *parent = 0);
	~sexComboDelegate(void);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

     void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif