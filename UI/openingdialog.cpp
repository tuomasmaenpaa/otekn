/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */
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
