#pragma once
#include "PuzzleSelectGameEngine.h"
#include"PuzzleGames.h"
#include"qpushbutton.h"
#include"BlockSlideTile.h"
#include"GameLayout.h"
class BlockSlideEngine :
    public PuzzleSelectGameEngine {
public:
    BlockSlideEngine(PuzzleGames* controller);
    ~BlockSlideEngine();

    void setupTiles();
    void checkIfWin();

    void startEngine();
    void resetGame();
    void startGame();

    void createSlidingBlock(int row, int col);

    void highlightPossibleMoves(SlidingBlock* block);
    void highlightToTheRight(SlidingBlock* block);
    void highlightToTheLeft(SlidingBlock* block);
    void highlightAbove(SlidingBlock* block);
    void highlightBelow(SlidingBlock* block);
    void clearHighlights();

    void enableButtons();
    void disableButtons();

    void moveCurrentBlock(std::array<int, 2> newCoords);
    void moveSmoothly(std::array<int, 2> newCoords);
    void updateBlock();

    void putLayoutIntoTileGrid();

    void setTileAsBarrier(int i, int j);
    void setTileAsGoal(int i, int j);
    void setTileAsDefault(int i, int j);

    bool eventFilter(QObject* watched, QEvent* event);

    void increasePuzzleIndex();
    void decreasePuzzleIndex();

public slots:
    void tileBtnClick();
    void slidingBlockBtnRightClick();
    void slidingBlockBtnClick();
    void animationFinished();
private:
    PuzzleGames* controller;
    std::array<std::array<BlockSlideTile, 6>, 6> tiles;
    GameLayout<6> currentLayout;
    std::vector<SlidingBlock*> slidingBlocks;
    bool gameActive{ false };
    std::array<int, 2> winCoords;
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    SlidingBlock* currentSelectedBlock;
    bool animationActive;
    int numGoals{ 0 };
    bool resetOnlyThePuzzle{ false };

};

