#include "PosButton.h"
#include "ui_PosButton.h"

#include <QPushButton>

PosButton::PosButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PosButton)
{
	ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked(bool)), this, SIGNAL(pressed()));
}

PosButton::~PosButton()
{
	delete ui;
}
