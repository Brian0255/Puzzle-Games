#pragma once
#include<qobject.h>
#include"PuzzleGames.h"
#include"GameEngine.h"
#include"qpushbutton.h"
#include"MinesweeperTile.h"
#include<array>

class MinesweeperEngine : public GameEngine {
    Q_OBJECT

public:
    MinesweeperEngine(PuzzleGames* controller);
    ~MinesweeperEngine();

    void startEngine();
    void resetGame();

public slots:
    void tileButtonPress();
    void tileButtonClick();
    void tileRightClick();
    void tileMiddleClick();
    void resetButtonClick();
private:
    PuzzleGames* controller;
    int bombs;
    int bombStartAmount{ 30 };
    std::array<std::array<MinesweeperTile, 16>, 16> tiles;
    bool gameActive{ false };
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    std::map<std::array<int, 2>, bool> bombCoordsUsed;

    void setupTiles();
    void startGame(QPushButton*, int);

    void gameOver(QPushButton*);

    void revealTile(QPushButton* button);

    void checkIfWin();

    int calcFlagsAroundTile(QPushButton* button);
    void setupTileBombCounts();
};