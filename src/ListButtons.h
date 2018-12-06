#ifndef LISTBUTTONS_H
#define LISTBUTTONS_H

#include <QWidget>

namespace Ui {
class ListButtons;
}

/**
 * @brief ListButtons class
 *
 * This class is used with the Ui that deals with buttons for the list
 */
class ListButtons : public QWidget
{
	Q_OBJECT
	
public:
    /**
     * @brief Constructor
     * @param parent
     */
	explicit ListButtons(QWidget *parent = nullptr);
    /**
     * @brief Destructor
     */
    ~ListButtons();
	
	void setRemoveEnabled(bool);
	
signals:
    /**
     * @brief add
     */
	void add();

    /**
     * @brief remove
     */
	void remove();
	
private:
	Ui::ListButtons *ui;
};

#endif // LISTBUTTONS_H
