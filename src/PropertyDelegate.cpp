#include "PropertyDelegate.h"

#include "PropertyItem.h"

#include <QComboBox>
#include <QSpinBox>
#include <QTreeWidget>

PropertyDelegate::PropertyDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
	connect(this, &PropertyDelegate::valueChanged, this, &PropertyDelegate::commitData);
}

const char* QOBJ_PROP_NAME = "DataType";

QWidget* PropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex& index) const
{
	if (index.column() == 0) {
		return nullptr;
	}
	
	int type = getType(parent);
	
#define TEXT_SELECTION(source) do { \
	QComboBox* editor = new QComboBox{parent}; \
	editor->setProperty(QOBJ_PROP_NAME, type); \
	QStringList strings = source; \
	editor->insertItems(0, strings); \
	editor->setEditable(false); \
	return editor; \
} while (0)
	
	switch (type) {
	case PropBrushStyle:
		TEXT_SELECTION(BRUSH_STYLE_NAMES.values());
		break;
	case PropColor:
		TEXT_SELECTION(COLOR_NAMES.keys());
		break;
	default:
		QSpinBox *editor = new QSpinBox(parent);
		editor->setProperty(QOBJ_PROP_NAME, type);
		editor->setFrame(false);
		editor->setMinimum(0);
		editor->setMaximum(1000);
		return editor;
	}
}

void PropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int type = editor->property(QOBJ_PROP_NAME).value<int>();
	switch (type) {
	case PropBrushStyle:
	case PropColor: {
		QComboBox* comboBox = dynamic_cast<QComboBox*>(editor);
		QString value = index.model()->data(index, Qt::EditRole).value<QString>();
		
		comboBox->setCurrentText(value);
		connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, std::bind(&PropertyDelegate::valueChanged, this, editor));
		break;
	}
	default:
		QSpinBox* spinBox = dynamic_cast<QSpinBox*>(editor);
		int value = index.model()->data(index, Qt::EditRole).toInt();
		
		spinBox->setValue(value);
		connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, std::bind(&PropertyDelegate::valueChanged, this, editor));
	}
}

void PropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	int type = editor->property(QOBJ_PROP_NAME).value<int>();
	switch (type) {
	case PropBrushStyle:
	case PropColor: {
		QComboBox* comboBox = dynamic_cast<QComboBox*>(editor);
		QString value = comboBox->currentText();
		
		model->setData(index, value, Qt::EditRole);
		break;
	}
	default:
		QSpinBox* spinBox = dynamic_cast<QSpinBox*>(editor);
		spinBox->interpretText();
		int value = spinBox->value();
		
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

