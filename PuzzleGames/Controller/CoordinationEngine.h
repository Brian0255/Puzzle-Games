#pragma once
#include "PuzzleSelectGameEngine.h"
#include"PuzzleGames.h"
#include"CoordinationTile.h"
#include"GameLayout.h"
#include<vector>
#include<array>
#include<map>

class CoordinationEngine :
    public PuzzleSelectGameEngine {
public:
    CoordinationEngine(PuzzleGames* controller);
    ~CoordinationEngine();

    void startEngine();
    void startGame();
    void resetGame();

    void setupTiles();
    void putLayoutIntoTileGrid();

    void checkIfWin();

    void tryToMoveOtherBlocks(std::array<int, 2> differenceToMove);
    void moveBlock(std::array<int, 2> blockCoords, std::array<int, 2> differenceToMove);

    bool coordInBounds(std::array<int, 2> coords);
    bool isNeighboringCurrentTile(CoordinationTile* tile);

    bool eventFilter();

public slots:
    void tileButtonClick();
    void coordBlockPress();
    void coordBlockRelease();
private:
    PuzzleGames* controller;
    std::array<std::array<CoordinationTile, 7>, 7> tiles;
    std::vector<std::array<int, 2>> allBlockCoords;
    std::array<int, 2> activeBlockCoords;
    bool currentlyMoving;
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    GameLayout<7> currentLayout;
};

