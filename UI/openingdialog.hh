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

    int getSpinBoxValue();
private:
    Ui::OpeningDialog *ui;
};

#endif // OPENINGDIALOG_HH
