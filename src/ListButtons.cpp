#include "ListButtons.h"
#include "ui_ListButtons.h"

ListButtons::ListButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListButtons)
{
	ui->setupUi(this);
}

ListButtons::~ListButtons()
{
	delete ui;
}

