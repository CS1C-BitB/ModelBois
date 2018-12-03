#ifndef LISTBUTTONS_H
#define LISTBUTTONS_H

#include <QWidget>

namespace Ui {
class ListButtons;
}

class ListButtons : public QWidget
{
	Q_OBJECT
	
public:
	explicit ListButtons(QWidget *parent = nullptr);
	~ListButtons();
	
	void setRemoveEnabled(bool);
	
signals:
	void add();
	void remove();
	
private:
	Ui::ListButtons *ui;
};

#endif // LISTBUTTONS_H
