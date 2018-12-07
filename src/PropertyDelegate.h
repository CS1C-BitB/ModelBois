#ifndef PROPERTYDELEGATE_H
#define PROPERTYDELEGATE_H

#include <QStyledItemDelegate>

// user interface delegate on the side --

/**
 * @brief PropertyDelegate class
 *
 * This class allows the user to interface with the property items. This class manages
 * the interface that allows the user to change the attributes about the shape. This
 * class is derived from the QStyleItemDelegate
 */
class PropertyDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
    /**
     * @brief Constuctor
     * @param parent
     */
	PropertyDelegate(QObject* parent = nullptr);

    /**
     * @brief createEditor, init attributes
     * @param parent
     * @param option
     * @param index
     * @return qwidget object
     *
     * This function sets up various list of attributes that can modify the shapes
     * This function creates a list of options for each attribute that the user
     * can interface with
     */
	QWidget *createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    /**
     * @brief setEditorData, gets info about the shape from the editor
     * @param editor
     * @param index
     */
	void setEditorData(QWidget* editor, const QModelIndex& index) const override;

    /**
     * @brief setModelData, gets model data from the editor
     * @param editor
     * @param model
     * @param index
     */
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

    /**
     * @brief updateEditorGeometry, updates the geometry of the editor
     * @param editor
     * @param option
     * @param index
     */
	void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	
private:
	Q_SIGNAL void valueChanged(QWidget*) const;
};
#endif // PROPERTYDELEGATE_H
