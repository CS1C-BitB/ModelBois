#ifndef POSBUTTON_H
#define POSBUTTON_H

#include <QPushButton>
#include <QWidget>

namespace Ui {
class ItemButton;
}

/**
 * @brief PosButton class
 *
 * This class represents objects which are used for position buttons
 */
class ItemButton : public QWidget
{
	Q_OBJECT
	
public:
	/**
	 * @brief PosButton
	 * @param parent
	 */
	explicit ItemButton(const QList<QPair<QIcon, QString>> &buttons, QWidget *parent = nullptr);

	/**
	 * @brief Destructor
	 */
	~ItemButton();
	
	QPushButton* button(int i);
	
signals:
	/**
	 * @brief the position buttons register a click by the user
	 */
	void clicked(int i);
	
private:
	QVector<QPushButton*> buttons;
	Ui::ItemButton *ui;
};

#endif // POSBUTTON_H
