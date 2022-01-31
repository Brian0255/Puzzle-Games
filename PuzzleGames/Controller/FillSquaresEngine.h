#pragma once
#include "GameEngine.h"
#include"FillSquaresTile.h"
#include"FillSquareLayout.h"
#include"PuzzleGames.h"

class FillSquaresEngine :
    public GameEngine {
public:
    FillSquaresEngine(PuzzleGames* controller);
    ~FillSquaresEngine();
    void setupTiles();
    void resetFill();
    void checkIfWin();
    void startEngine();
    void resetGame();
    void startGame();
    void disableButtons();
    void putLayoutIntoTileGrid(FillSquareLayout layout);
    void setTileAsBlockedOff(int i, int j);
    bool isNeighboringCurrentTile(FillSquaresTile* tile);
    bool eventFilter(QObject* watched, QEvent* event);
    void goForward(QPushButton*& lastFilled, FillSquaresTile* tile, QPushButton*& btn);
    void goBackwards(QPushButton*& lastFilled, QPushButton* btn);
    void updateColors();
    void resetTiles();
    void rotateLayoutRandomly(FillSquareLayout& layout);
    void rotate90Degrees(FillSquareLayout& layout);
    void transposeLayout(FillSquareLayout& layout);
public slots:
    void tileButtonPress();
    void tileButtonClick();
    void tileRightClick();
private:
    PuzzleGames* controller;
    std::array<std::array<FillSquaresTile, 8>, 8> tiles;
    FillSquareLayout currentLayout;
    bool currentlyFilling{ false };
    bool gameActive{ false };
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    std::vector<QPushButton*> buttonFillSequence;
};

