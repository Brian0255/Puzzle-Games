#pragma once
#include "GameEngine.h"
#include"PuzzleGames.h"
#include"BattleshipShip.h"
#include"BattleshipTile.h"
class BattleshipEngine :
    public GameEngine {
    Q_OBJECT

public:
    BattleshipEngine(PuzzleGames* controller);
    ~BattleshipEngine();
    void startEngine();
    void setupTiles();
    void startGame();
    void revealTile(QPushButton* button);
    void resetGame();
    void gameOver();
    void checkIfWin();
    void disableButtons();
    void setupTileShipCounts();
public slots:
    void tileButtonPress();
    void tileButtonClick();
    void tileRightClick();
private:
    PuzzleGames* controller;
    int clicksLeft;
    int shipsRemaining;
    std::vector<BattleshipShip> ships;
    std::array<int, 3> shipLengths{ 4,3,2 };
    std::array<char, 12> shipLetters{ 'A','B','C','D','E','F','G','H','I','J','K','L' };
    std::array<std::array<BattleshipTile, 10>, 10> tiles;
    bool gameActive{ false };
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    void calculateShipsRemaining();
    bool shipUncovered(BattleshipShip ship);
    bool checkIfShipFits(BattleshipShip ship);
    void createShip(std::string orientation, int size);
    void createHorizontalShip(int size);
    void createVerticalShip(int size);
    void addShip(BattleshipShip& potentialShip);
};

