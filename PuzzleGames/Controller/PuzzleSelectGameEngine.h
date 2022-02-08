#pragma once
#include "GameEngine.h"
class PuzzleSelectGameEngine :
    public GameEngine {
public:
    PuzzleSelectGameEngine(int totalPuzzles);

    void increasePuzzleIndex();
    void decreasePuzzleIndex();

    int getCurrentIndex();

    virtual void putLayoutIntoTileGrid() = 0;
private:
    int curPuzzleIndex;
    int totalPuzzles;
};

