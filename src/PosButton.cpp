#include "PosButton.h"
#include "ui_PosButton.h"

#include <QPushButton>

PosButton::PosButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PosButton)
{
	ui->setupUi(this);
	connect(ui->button, SIGNAL(clicked(bool)), this, SIGNAL(clicked()));
}

PosButton::~PosButton()
{
	delete ui;
}
