#pragma once
#include "GameEngine.h"
#include"BlockFillTile.h"
#include"BlockFillLayout.h"
#include"PuzzleGames.h"
class BlockFillEngine :
    public GameEngine {
public:
    BlockFillEngine(PuzzleGames* controller);
    ~BlockFillEngine();

    void checkIfWin();
    void setupTiles();

    void startEngine();
    void startGame();
    void resetGame();
    void resetTiles();

    void putLayoutIntoTileGrid();

    void disableButtons();
    void enableButtons();

    void createShape(BlockFillLayout layout, int row, int col);
    void connectShapeWithTiles(BlockFillShape* shape);
    void changeTileColorToShape(BlockFillTile* tile);

    void clearCurrentShapeColors();
    void fillCurrentShapeColors();
    bool overlapAtCurrentSpot();

    void increasePuzzleIndex();
    void decreasePuzzleIndex();

    int getCurrentIndex();

    void highlightShape(BlockFillShape* shape);
    void unhighlightShape(BlockFillShape* shape);

    bool eventFilter(QObject* watched, QEvent* event);

    void handleButtonEventFilter(QEvent* event, QPushButton*& btn);
    void handleFrameEventFilter(QEvent* event);
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
    int curPuzzleIndex;
    int totalPuzzles;
    std::array<int, 2> lastMouseGridPosition;
};

