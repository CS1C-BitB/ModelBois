#ifndef POSBUTTON_H
#define POSBUTTON_H

#include <QWidget>

namespace Ui {
class PosButton;
}

class PosButton : public QWidget
{
	Q_OBJECT
	
public:
	explicit PosButton(QWidget *parent = nullptr);
	~PosButton();
	
signals:
	void clicked();
	
private:
	Ui::PosButton *ui;
};

#endif // POSBUTTON_H
