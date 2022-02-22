#pragma once
#include "GameEngine.h"
class PuzzleSelectGameEngine :
    public GameEngine {
public:
    PuzzleSelectGameEngine(int totalPuzzles);

    void increasePuzzleIndex();
    void decreasePuzzleIndex();

    int getCurrentIndex();

private:
    int curPuzzleIndex;
    int totalPuzzles;

    virtual void putLayoutIntoTileGrid() = 0;
};

