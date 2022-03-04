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

    bool startEngine();
    bool resetGame();

    bool eventFilter(QObject* watched, QEvent* event);

public slots:
    void tileButtonClick();
    void tileButtonRelease();
private:
    PuzzleGames* controller;
    std::array<std::array<CoordinationTile, 7>, 7> tiles;
    std::vector<std::array<int, 2>> allBlockCoords;
    std::array<int, 2> activeBlockCoords;
    bool currentlyMoving;
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    GameLayout<7> currentLayout;

    void startGame();
    void setupTiles();

    void putLayoutIntoTileGrid();

    void checkIfWin();

    void moveAllBlocks(std::array<int, 2> differenceToMove);
    void moveBlock(int index, std::vector<std::array<int, 2>>& newCoords);

    bool checkForOverlapError(std::vector<std::array<int, 2>>& oldCoords, std::vector<std::array<int, 2>>& newCoords);

    void setTilesToNewBlockCoords();
    void calculateNewBlockCoords(std::vector<std::array<int, 2>>& newCoords);
    void clearOutOldBlockPositions();

    bool checkIfValidMove(const std::array<int, 2>& differenceToMove);

    bool coordInBounds(std::array<int, 2> coords);
    bool isNeighboringCurrentTile(CoordinationTile* tile);
    bool validSpotForBlock(std::array<int, 2> coords);
};

