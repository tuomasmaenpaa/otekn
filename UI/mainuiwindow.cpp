#include "mainuiwindow.hh"
#include "ui_mainuiwindow.h"
#include <iostream>

MainUiWindow::MainUiWindow(QGraphicsView* view, std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<Student::GameBoard> board, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUiWindow),
    _scene(scene),
    _board(board)

{
    ui->setupUi(this);
    view->setScene(_scene.get());

    ui->graphicsView->setScene(_scene.get());

    std::shared_ptr<Student::graphicHex> gHexPtr;
    Student::graphicHex* hexPtr;

    for(auto a : _board->getGraphicHexMap()){

        gHexPtr = a.second;
        hexPtr=gHexPtr.get();

        connect(hexPtr, &Student::graphicHex::clickHappened, this, &MainUiWindow::tileClicked);
    }


    //setCentralWidget(view);
    //view->show();
}

MainUiWindow::~MainUiWindow()
{
    delete ui;
}

void MainUiWindow::tileClicked()
{
    std::cout<<"Here"<<std::endl;
}
