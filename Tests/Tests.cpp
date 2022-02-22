#include <QtTest>
#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include<../PuzzleGames/Model/ArrayUtils.h>
#include<../PuzzleGames/Model/ColorUtils.h>
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
    void test_colorChangeBasic();
    void test_colorChangeEdgeCase();

    void test_colorGetBasic();
    void test_colorGetEdgeCase();

    void test_arrayAddBasic();
    void test_arrayAddEdgeCase();

    void test_arraySubBasic();
    void test_arraySubEdgeCase();
};

Tests::Tests()
{

}

Tests::~Tests()
{

}

void Tests::test_arrayAddBasic(){
    std::array<int,arrSize3> arr1 = {1,2,3};
    std::array<int,arrSize3> arr2 = {3,4,0};

    std::array<int,arrSize3> expected = {4,6,3};
    std::array<int,arrSize3> actual = ArrayUtils::addIntArrays(arr1,arr2);
    QVERIFY(expected == actual);
}

void Tests::test_arrayAddEdgeCase(){
    std::array<int,arrSize0> arr1 = {};
    std::array<int,arrSize0> arr2 = {};

    std::array<int,arrSize0> expected = {};
    std::array<int,arrSize0> actual = ArrayUtils::addIntArrays(arr1,arr2);
    QVERIFY(expected == actual);
}

void Tests::test_arraySubBasic(){
    std::array<int,arrSize3> arr1 = {1,0,6};
    std::array<int,arrSize3> arr2 = {1,3,0};

    std::array<int,arrSize3> expected = {0,-3,6};
    std::array<int,arrSize3> actual = ArrayUtils::subtractIntArrays(arr1,arr2);
    QVERIFY(expected == actual);
}

void Tests::test_arraySubEdgeCase(){
    std::array<int,arrSize0> arr1 = {};
    std::array<int,arrSize0> arr2 = {};

    std::array<int,arrSize0> expected = {};
    std::array<int,arrSize0> actual = ArrayUtils::subtractIntArrays(arr1,arr2);
    QVERIFY(expected == actual);
}

void Tests::test_colorChangeBasic()
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

void Tests::test_colorChangeEdgeCase()
{
    QPushButton* button = new QPushButton();

    QPushButton* expected = new QPushButton();
    expected->setStyleSheet(
      "background-color: rgb(200,200,200);"
    );
    ColorUtils::changeColor(button,"background-color: rgb(200,200,200);");
    QVERIFY(button->styleSheet() == expected->styleSheet());
}

void Tests::test_colorGetBasic()
{
    QPushButton* button = new QPushButton();
    button->setStyleSheet(
      "background-color: rgb(100,100,100);"
    );
    QString expected = "background-color: rgb(100,100,100);";
    QString actual = ColorUtils::getColor(button);
    QVERIFY(expected==actual);
}

void Tests::test_colorGetEdgeCase()
{
    QPushButton* button = new QPushButton();
    QString expected = "";
    QString actual = ColorUtils::getColor(button);
    QVERIFY(expected==actual);
}

QTEST_MAIN(Tests)

#include "Tests.moc"
