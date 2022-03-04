#include <QtTest>
#include <QCoreApplication>
#include<QtWidgets/qapplication.h>
#include <QtWidgets/QPushButton>
#include"qmainwindow.h"
#include "ArrayUtils.h"
#include "ColorUtils.h"
#include"BattleshipEngine.h"
#include"MinesweeperEngine.h"
#include"CoordinationEngine.h"
#include"BlockFillEngine.h"
#include"FillSquaresEngine.h"
#include"BlockSlideEngine.h"
#include"PuzzleGames.h"
#include"qdebug.h"
#include<iostream>
// add necessary includes here

#define arrSize3 3
#define arrSize0 0

class Tests : public QObject
{
    Q_OBJECT


public:
    Tests();
    ~Tests();

private slots:
    void changeColor_noColorExists();
    void changeColor_generalCase();

    void getColor_generalCase();
    void getColor_noColorExists();

    void addIntArrays_generalCase();
    void addIntArrays_emptyArrays();

    void subIntArrays_generalCase();
    void subIntArrays_emptyArrays();

    void MinesweeperEngine_startEngine_NULLController();
    void MinesweeperEngine_resetGame_engineNotStarted();

    void BattleshipEngine_startEngine_NULLController();
    void BattleshipEngine_resetGame_engineNotStarted();

    void FillSquaresEngine_startEngine_NULLController();
    void FillSquaresEngine_resetGame_engineNotStarted();

    void BlockFillEngine_startEngine_NULLController();
    void BlockFillEngine_resetGame_engineNotStarted();

    void CoordinationEngine_startEngine_NULLController();
    void CoordinationEngine_resetGame_engineNotStarted();

    void BlockSlideEngine_startEngine_NULLController();
    void BlockSlideEngine_resetGame_engineNotStarted();
};

Tests::Tests()
{
}

Tests::~Tests()
{

}

void Tests::addIntArrays_generalCase(){
    std::array<int,arrSize3> arr1 = {1,2,3};
    std::array<int,arrSize3> arr2 = {3,4,0};

    std::array<int,arrSize3> expected = {4,6,3};
    std::array<int,arrSize3> actual = ArrayUtils::addIntArrays(arr1,arr2);
    QVERIFY(expected == actual);
}

void Tests::addIntArrays_emptyArrays(){
    std::array<int,arrSize0> arr1 = {};
    std::array<int,arrSize0> arr2 = {};

    std::array<int,arrSize0> expected = {};
    std::array<int,arrSize0> actual = ArrayUtils::addIntArrays(arr1,arr2);
    QVERIFY(expected == actual);
}

void Tests::subIntArrays_generalCase(){
    std::array<int,arrSize3> arr1 = {1,0,6};
    std::array<int,arrSize3> arr2 = {1,3,0};

    std::array<int,arrSize3> expected = {0,-3,6};
    std::array<int,arrSize3> actual = ArrayUtils::subtractIntArrays(arr1,arr2);
    QVERIFY(expected == actual);
}

void Tests::subIntArrays_emptyArrays(){
    std::array<int,arrSize0> arr1 = {};
    std::array<int,arrSize0> arr2 = {};

    std::array<int,arrSize0> expected = {};
    std::array<int,arrSize0> actual = ArrayUtils::subtractIntArrays(arr1,arr2);
    QVERIFY(expected == actual);
}

void Tests::MinesweeperEngine_startEngine_NULLController() {
    MinesweeperEngine* engine = new MinesweeperEngine(NULL);
    bool success = engine->startEngine();
    QVERIFY(success == false);
}

void Tests::MinesweeperEngine_resetGame_engineNotStarted() {
    PuzzleGames controller;
    MinesweeperEngine* engine = new MinesweeperEngine(&controller);
    bool success = engine->resetGame();
    QVERIFY(success == false);
}

void Tests::BattleshipEngine_startEngine_NULLController() {
    BattleshipEngine* engine = new BattleshipEngine(NULL);
    bool success = engine->startEngine();
    QVERIFY(success == false);
}

void Tests::BattleshipEngine_resetGame_engineNotStarted() {
    PuzzleGames controller;
    BattleshipEngine* engine = new BattleshipEngine(&controller);
    bool success = engine->resetGame();
    QVERIFY(success == false);
}


void Tests::FillSquaresEngine_startEngine_NULLController() {
    FillSquaresEngine* engine = new FillSquaresEngine(NULL);
    bool success = engine->startEngine();
    QVERIFY(success == false);
}

void Tests::FillSquaresEngine_resetGame_engineNotStarted() {
    PuzzleGames controller;
    FillSquaresEngine* engine = new FillSquaresEngine(&controller);
    bool success = engine->resetGame();
    QVERIFY(success == false);
}

void Tests::BlockSlideEngine_startEngine_NULLController() {
    BlockSlideEngine* engine = new BlockSlideEngine(NULL);
    bool success = engine->startEngine();
    QVERIFY(success == false);
}

void Tests::BlockSlideEngine_resetGame_engineNotStarted() {
    PuzzleGames controller;
    BlockSlideEngine* engine = new BlockSlideEngine(&controller);
    bool success = engine->resetGame();
    QVERIFY(success == false);
}

void Tests::BlockFillEngine_startEngine_NULLController() {
    BlockFillEngine* engine = new BlockFillEngine(NULL);
    bool success = engine->startEngine();
    QVERIFY(success == false);
}

void Tests::BlockFillEngine_resetGame_engineNotStarted() {
    PuzzleGames controller;
    BlockFillEngine* engine = new BlockFillEngine(&controller);
    bool success = engine->resetGame();
    QVERIFY(success == false);
}

void Tests::CoordinationEngine_startEngine_NULLController() {
    CoordinationEngine* engine = new CoordinationEngine(NULL);
    bool success = engine->startEngine();
    QVERIFY(success == false);
}

void Tests::CoordinationEngine_resetGame_engineNotStarted() {
    PuzzleGames controller;
    CoordinationEngine* engine = new CoordinationEngine(&controller);
    bool success = engine->resetGame();
    QVERIFY(success == false);
}

void Tests::changeColor_generalCase()
{
    QPushButton* button = new QPushButton();
    button->setStyleSheet(
      "background-color: rgb(100,100,100);"
    );
    QPushButton* expected = new QPushButton();
    expected->setStyleSheet(
      "background-color: rgb(200,200,200);"
    );
    ColorUtils::changeColor(button,"background-color: rgb(200,200,200);");
    QVERIFY(button->styleSheet() == expected->styleSheet());
}

void Tests::changeColor_noColorExists()
{
    QPushButton* button = new QPushButton();

    QPushButton* expected = new QPushButton();
    expected->setStyleSheet(
      "background-color: rgb(200,200,200);"
    );
    ColorUtils::changeColor(button,"background-color: rgb(200,200,200);");
    QVERIFY(button->styleSheet() == expected->styleSheet());
}

void Tests::getColor_generalCase()
{
    QPushButton* button = new QPushButton();
    button->setStyleSheet(
      "background-color: rgb(100,100,100);"
    );
    QString expected = "background-color: rgb(100,100,100);";
    QString actual = ColorUtils::getColor(button);
    QVERIFY(expected==actual);
}

void Tests::getColor_noColorExists()
{
    QPushButton* button = new QPushButton();
    QString expected = "";
    QString actual = ColorUtils::getColor(button);
    QVERIFY(expected==actual);
}

QTEST_MAIN(Tests);

#include "Tests.moc"
