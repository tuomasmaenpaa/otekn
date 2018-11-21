#include "openingdialog.hh"
#include "ui_openingdialog.h"

OpeningDialog::OpeningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpeningDialog)
{
    ui->setupUi(this);
    setWindowTitle("Island Game");

}

OpeningDialog::~OpeningDialog()
{
    delete ui;
}

int OpeningDialog::getSpinBoxValue()
{
    return ui->playerSpinBox->value();
}
