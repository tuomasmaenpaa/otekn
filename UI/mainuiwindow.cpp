#include "mainuiwindow.hh"
#include "ui_mainuiwindow.h"
#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <map>
#include <QMessageBox>



const std::map <Common::GamePhase,QString> PHASES = {{Common::MOVEMENT,"Movement"},
                                                     {Common::SINKING,"Sinking"},
                                                     {Common::SPINNING,"Spinning"}};

MainUiWindow::MainUiWindow(std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<Student::GameBoard> board,
                           std::shared_ptr<Common::IGameRunner> runner, std::shared_ptr <Student::GameState> state, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUiWindow),
    _scene(scene),
    _board(board),
    _runner(runner),
    _state(state)


{
    ui->setupUi(this);

    ui->graphicsView->setScene(_scene.get());

    std::shared_ptr<Student::graphicHex> gHexPtr;
    Student::graphicHex* hexPtr;

    for(auto a : _board->getGraphicHexMap()){

        gHexPtr = a.second;
        hexPtr=gHexPtr.get();

        connect(hexPtr, &Student::graphicHex::clickHappened, this, &MainUiWindow::tileClicked);
    }


    connect(ui->spinWheelPushButton,&QPushButton::clicked, this, &MainUiWindow::spinWheel);
    ui->spinWheelPushButton->setDisabled(true);

    connect(ui->endTurnPushButton,&QPushButton::clicked, this, &MainUiWindow::endTurn);

    updateLabels();


}

MainUiWindow::~MainUiWindow()
{
    delete ui;
}

void MainUiWindow::updateLabels()
{
    Common::GamePhase phase = _runner->currentGamePhase();

    if(PHASES.find(phase)!= PHASES.end()){
        ui->gamePhaseLabel->setText(PHASES.at(phase));
    }


    QString turn = "Player " + QString::number(_runner->getCurrentPlayer()->getPlayerId()) + " turn";
    ui->playerTurnLabel->setText(turn);

    if(_state->currentGamePhase() == Common::SPINNING){
        ui->spinWheelPushButton->setDisabled(false);
    }else{
        ui->spinWheelPushButton->setDisabled(true);
    }

    update();



}

bool MainUiWindow::victoryRoyale()
{
    return _board->winCheck();
}

void MainUiWindow::tileClicked(std::shared_ptr<Common::Hex> clickedHex)
{

    if ( _runner->currentGamePhase() == Common::MOVEMENT){
        //move
        _board->setClickedMovement(clickedHex);

        //If the game is won
        if(victoryRoyale()){

            QMessageBox box;
            box.setText("VICTORY ROYALE");
            box.setIcon(QMessageBox::Warning);
            box.exec();
            close();
        }



    }else if ( _runner->currentGamePhase() == Common::SINKING){
        //sink
        _board->setClickedSinking(clickedHex);

    }else if( _runner->currentGamePhase() == Common::SPINNING){
        //spin
        _board->setClickedSpinning(clickedHex,_wheelValues);

    }


    updateLabels();


}

void MainUiWindow::spinWheel()
{
    std::pair<std::string,std::string> values;
    values=_runner->spinWheel();

    _wheelValues = values;



    QString qstr = QString::fromStdString(values.first + " " + values.second);

    ui->wheelValueLabel->setText(qstr);


    Common::GamePhase phase = _runner->currentGamePhase();

    if(PHASES.find(phase)!= PHASES.end()){
        ui->gamePhaseLabel->setText(PHASES.at(phase));
    }




    update();
    updateLabels();

}

void MainUiWindow::endTurn()
{
    _board->nextPlayer();
    updateLabels();

}
