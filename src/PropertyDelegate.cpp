#include "PropertyDelegate.h"

#include "PropertyItem.h"

#include <QComboBox>
#include <QSpinBox>
#include <QTreeWidget>

PropertyDelegate::PropertyDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{ }

QWidget* PropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
	int type = getType(parent);
	
	switch (type) {
	case PropBrush: {
		QComboBox* editor = new QComboBox{parent};
		QStringList strings = BRUSH_STYLE_NAMES.values();
		editor->insertItems(0, strings);
		editor->setEditable(false);
		return editor;
	}
	case PropColor: {
		QSpinBox *editor = new QSpinBox(parent);
		editor->setFrame(false);
		editor->setMinimum(0);
		editor->setMaximum(255);
		return editor;
	}
	default:
		QSpinBox *editor = new QSpinBox(parent);
		editor->setFrame(false);
		editor->setMinimum(0);
		editor->setMaximum(1000);
		return editor;
	}
}

void PropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (QSpinBox* spinBox = dynamic_cast<QSpinBox*>(editor)) {
		int value = index.model()->data(index, Qt::EditRole).toInt();
		
		spinBox->setValue(value);
	}
	else if (QComboBox* comboBox = dynamic_cast<QComboBox*>(editor)) {
		QString value = index.model()->data(index, Qt::EditRole).toString();
		
		comboBox->setCurrentText(value);
	}
}

void PropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	if (QSpinBox* spinBox = dynamic_cast<QSpinBox*>(editor)) {
		spinBox->interpretText();
		int value = spinBox->value();
		
		model->setData(index, value, Qt::EditRole);
	}
	else if (QComboBox* comboBox = dynamic_cast<QComboBox*>(editor)) {
		QString value = comboBox->currentText();
		
		model->setData(index, value, Qt::EditRole);
	}
}

void PropertyDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex&) const
{
	editor->setGeometry(option.rect);
}

int PropertyDelegate::getType(QWidget *parent) const
{
	QTreeWidget* tree = static_cast<QTreeWidget*>(parent->parent());
	QTreeWidgetItem* item = tree->currentItem();
	int type = item->type();
	if (type == Qt::UserRole) {
		type = item->parent()->type();
	}
	return type;
}

