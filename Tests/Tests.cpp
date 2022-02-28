#include <QtTest>
#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include<../PuzzleGames/Model/ArrayUtils.h>
#include<../PuzzleGames/Model/ColorUtils.h>
#include<../PuzzleGames/Controller/BattleshipEngine.h>
#include<../PuzzleGames/Controller/PuzzleGames.h>
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

    void BattleshipEngine_startEngine_generalCase();
    void BattleshipEngine_startEngine_NULLController();
    void BattleshipEngine_resetGame_engineNotStarted();
    void BattleshipEngine_resetGame_generalCase();


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

void Tests::BattleshipEngine_startEngine_generalCase() {
}

void Tests::BattleshipEngine_startEngine_NULLController() {
}

void Tests::BattleshipEngine_resetGame_engineNotStarted() {
}

void Tests::BattleshipEngine_resetGame_generalCase() {
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

QTEST_MAIN(Tests)

#include "Tests.moc"
