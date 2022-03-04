#pragma once
#include "GameEngine.h"
#include"FillSquaresTile.h"
#include"GameLayout.h"
#include"PuzzleGames.h"

class FillSquaresEngine :
    public GameEngine {
public:
    FillSquaresEngine(PuzzleGames* controller);
    ~FillSquaresEngine();

    bool startEngine();
    bool resetGame();

    bool eventFilter(QObject* watched, QEvent* event);

public slots:
    void tileButtonPress();
    void tileButtonClick();
    void tileRightClick();
private:
    PuzzleGames* controller;
    std::array<std::array<FillSquaresTile, 8>, 8> tiles;
    GameLayout<8> currentLayout;
    bool currentlyFilling{ false };
    bool gameActive{ false };
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    std::vector<QPushButton*> buttonFillSequence;

    void startGame();

    void goForward(QPushButton*& lastFilled, FillSquaresTile* tile, QPushButton*& btn);
    void goBackwards(QPushButton*& lastFilled, QPushButton* btn);

    void updateColors();
    void resetTiles();

    void rotateLayoutRandomly();
    void rotate90Degrees();
    void transposeLayout();

    void putLayoutIntoTileGrid();

    void setTileAsBlockedOff(int i, int j);
    bool isNeighboringCurrentTile(FillSquaresTile* tile);

    void setupTiles();
    void resetFill();

    void checkIfWin();
};

