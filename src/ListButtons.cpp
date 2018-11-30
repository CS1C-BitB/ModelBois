#include "ListButtons.h"
#include "ui_ListButtons.h"

#include <QPushButton>

ListButtons::ListButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListButtons)
{
	ui->setupUi(this);
	connect(ui->add, SIGNAL(clicked(bool)), this, SIGNAL(add()));
	connect(ui->remove, SIGNAL(clicked(bool)), this, SIGNAL(remove()));
}

ListButtons::~ListButtons()
{
	delete ui;
}

void ListButtons::setRemoveEnabled(bool enable)
{
	ui->remove->setEnabled(enable);
}

