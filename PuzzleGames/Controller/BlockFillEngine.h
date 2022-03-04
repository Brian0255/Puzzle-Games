#pragma once
#include "PuzzleSelectGameEngine.h"
#include"BlockFillTile.h"
#include"GameLayout.h"
#include"PuzzleGames.h"
class BlockFillEngine :
    public PuzzleSelectGameEngine {
public:
    BlockFillEngine(PuzzleGames* controller);
    ~BlockFillEngine();

    bool startEngine();
    bool resetGame();

    bool eventFilter(QObject* watched, QEvent* event);

public slots:
    void tileBtnClick();
    void placeCurrentBlock();
    void tileBtnRightClick();
    void setupShapeDrag(BlockFillTile* tile, QPushButton*& button);
private:
    PuzzleGames* controller;
    std::array<std::array<BlockFillTile, 16>, 16> tiles;
    std::vector<BlockFillShape*> shapes;
    bool gameActive{ false };
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    BlockFillShape* currentShape;
    bool dragging;
    std::array<int, 2> lastMouseGridPosition;

    void startGame();
    void checkIfWin();
    void setupTiles();
    void resetTiles();

    void putLayoutIntoTileGrid();

    void createShape(GameLayout<16> layout, int row, int col);
    void connectShapeWithTiles(BlockFillShape* shape);
    void changeTileColorToShape(BlockFillTile* tile);

    void clearCurrentShapeColors();
    void fillCurrentShapeColors();
    bool overlapAtCurrentSpot();

    void highlightShape(BlockFillShape* shape);
    void unhighlightShape(BlockFillShape* shape);

    void handleButtonEventFilter(QEvent* event, QPushButton*& btn);
    void handleFrameEventFilter(QEvent* event);


};

