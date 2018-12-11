#ifndef FONTSIZECOMBOBOX_H
#define FONTSIZECOMBOBOX_H

#include <QComboBox>

class FontSizeComboBox : public QComboBox
{
	Q_OBJECT
	
public:
	FontSizeComboBox(QWidget* parent = nullptr);
	
	void validate();
	int value();
};

#endif // FONTSIZECOMBOBOX_H
