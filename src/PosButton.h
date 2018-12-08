#ifndef POSBUTTON_H
#define POSBUTTON_H

#include <QWidget>

namespace Ui {
class PosButton;
}

/**
 * @brief PosButton class
 *
 * This class represents objects which are used for position buttons
 */
class PosButton : public QWidget
{
	Q_OBJECT
	
public:

	/**
	 * @brief PosButton
	 * @param parent
	 */
	explicit PosButton(QWidget *parent = nullptr);

	/**
	 * @brief Destructor
	 */
	~PosButton();
	
signals:
	/**
	 * @brief the position buttons register a click by the user
	 */
	void clicked();
	
private:
	Ui::PosButton *ui;
};

#endif // POSBUTTON_H
