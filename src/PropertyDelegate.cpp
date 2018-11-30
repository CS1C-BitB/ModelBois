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

//const char* QOBJ_PROP_NAME = "DataType";

QWidget* PropertyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem&, const QModelIndex& index) const
{
	if (index.column() == 0) {
		return nullptr;
	}
	
	QTreeWidget* tree = static_cast<QTreeWidget*>(parent->parent());
	QTreeWidgetItem* item = tree->currentItem();
	int type = item->type();
	
#define TEXT_SELECTION(source) do { \
	QComboBox* editor = new QComboBox{parent}; \
	QStringList strings = source; \
	editor->insertItems(0, strings); \
	editor->setEditable(false); \
	return editor; \
} while (0)
	
	switch (type) {
	case PropInt: {
		QSpinBox *editor = new QSpinBox(parent);
		editor->setFrame(false);
		editor->setMinimum(0);
		editor->setMaximum(1000);
		return editor;
	}
	case PropBrushStyle:
		TEXT_SELECTION(BRUSH_STYLE_NAMES.values());
		break;
	case PropColor:
		TEXT_SELECTION(COLOR_NAMES.keys());
		break;
	case PropPenStyle:
		TEXT_SELECTION(PEN_STYLE_NAMES.values());
		break;
	case PropPenCapStyle:
		TEXT_SELECTION(PEN_CAP_STYLE_NAMES.values());
		break;
	case PropPenJoinStyle:
		TEXT_SELECTION(PEN_JOIN_STYLE_NAMES.values());
		break;
	}
	
	return nullptr;
}

void PropertyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (QComboBox* comboBox = dynamic_cast<QComboBox*>(editor)) {
		QString value = index.model()->data(index, Qt::EditRole).value<QString>();
		
		comboBox->setCurrentText(value);
		connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, std::bind(&PropertyDelegate::valueChanged, this, editor));
	}
	else if (QSpinBox* spinBox = dynamic_cast<QSpinBox*>(editor)) {
		int value = index.model()->data(index, Qt::EditRole).toInt();
		
		spinBox->setValue(value);
		//connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, std::bind(&PropertyDelegate::valueChanged, this, editor));
	}
}

void PropertyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	if (QComboBox* comboBox = dynamic_cast<QComboBox*>(editor)) {
		QString value = comboBox->currentText();
		
		model->setData(index, value, Qt::EditRole);
	}
	else if (QSpinBox* spinBox = dynamic_cast<QSpinBox*>(editor)) {
		spinBox->interpretText();
		int value = spinBox->value();
		
		model->setData(index, value, Qt::EditRole);
	}
}

void PropertyDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex&) const
{
	editor->setGeometry(option.rect);
}

