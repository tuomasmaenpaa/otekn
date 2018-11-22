#include "mainuiwindow.hh"
#include "ui_mainuiwindow.h"

MainUiWindow::MainUiWindow(QGraphicsView* view, std::shared_ptr<QGraphicsScene> scene,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUiWindow),
    _scene(scene)

{
    ui->setupUi(this);
    view->setScene(_scene.get());

    ui->graphicsView->setScene(_scene.get());

    //setCentralWidget(view);
    //view->show();
}

MainUiWindow::~MainUiWindow()
{
    delete ui;
}
