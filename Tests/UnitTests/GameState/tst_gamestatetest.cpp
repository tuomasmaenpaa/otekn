#include <QString>
#include <QtTest>
#include "gamestate.hh"

class GameStateTest : public QObject
{
    Q_OBJECT

public:
    GameStateTest();


private Q_SLOTS:
    void testCurrentGamePhase();
    void testCurrentPlayer();
    void testChangeGamePhase();
    void testChangePlayerTurn();


private:
    Student::GameState _state;
};

GameStateTest::GameStateTest()
{
}


void GameStateTest::testCurrentGamePhase()
{
    QVERIFY(_state.currentGamePhase() == Common::MOVEMENT);
}

void GameStateTest::testCurrentPlayer()
{
    QVERIFY(_state.currentPlayer() == 1);
}

void GameStateTest::testChangeGamePhase()
{
    _state.changeGamePhase(Common::MOVEMENT);
    QVERIFY(_state.currentGamePhase() == Common::MOVEMENT);

    _state.changeGamePhase(Common::SINKING);
    QVERIFY(_state.currentGamePhase() == Common::SINKING);

    _state.changeGamePhase(Common::SPINNING);
    QVERIFY(_state.currentGamePhase() == Common::SPINNING);
}

void GameStateTest::testChangePlayerTurn()
{
    _state.changePlayerTurn(2);
    QVERIFY(_state.currentPlayer() == 2);
    QVERIFY(_state.currentGamePhase() == Common::MOVEMENT);
}



QTEST_APPLESS_MAIN(GameStateTest)

#include "tst_gamestatetest.moc"
