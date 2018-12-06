#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
class About;
}

/**
 *@brief About Class
 *
 * This class represents object used to display information about the program
 */
class About : public QDialog
{
	Q_OBJECT
	
public:
	/**
	 * @brief Constructor
	 * @param parent qwidget
	 */
	explicit About(QWidget *parent = nullptr);

	/**
	 * @brief Destructor
	 */
	~About();
	
private:
	Ui::About *ui;
};

#endif // ABOUT_H
