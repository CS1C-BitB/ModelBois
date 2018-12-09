#include "ItemButton.h"
#include "ui_ItemButton.h"

#include <QPushButton>

ItemButton::ItemButton(const QIcon& icon, const QString& tip, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemButton)
{
	ui->setupUi(this);
	
	ui->button->setIcon(icon);
	ui->button->setToolTip(tip);
	ui->button->setStatusTip(tip);
	
	connect(ui->button, SIGNAL(clicked(bool)), this, SIGNAL(clicked()));
}

ItemButton::~ItemButton()
{
	delete ui;
}
