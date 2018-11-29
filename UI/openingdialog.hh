/*
 * Tuomas Mäenpää, studentnumber 274403, tuomas.maenpaa@student.tut.fi
 * Peetu Ojala, studennumber 272729, peetu.ojala@student.tut.fi
 *
 * Programming 3 course project
 */

#ifndef OPENINGDIALOG_HH
#define OPENINGDIALOG_HH

#include <QDialog>

namespace Ui {
class OpeningDialog;
}

class OpeningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpeningDialog(QWidget *parent = 0);
    ~OpeningDialog();

    // Return the value of the spinwheel in the dialog window.
    int getSpinBoxValue();
private:
    Ui::OpeningDialog *ui;
};

#endif // OPENINGDIALOG_HH
