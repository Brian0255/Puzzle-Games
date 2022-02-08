#include "PuzzleSelectGameEngine.h"

PuzzleSelectGameEngine::PuzzleSelectGameEngine(int totalPuzzles)
	:totalPuzzles{ totalPuzzles }, curPuzzleIndex{ 0 } {
};

void PuzzleSelectGameEngine::increasePuzzleIndex() {
	curPuzzleIndex = (curPuzzleIndex + 1) % totalPuzzles;
	resetGame();
}

void PuzzleSelectGameEngine::decreasePuzzleIndex() {
	curPuzzleIndex = (curPuzzleIndex + totalPuzzles - 1) % totalPuzzles;
	resetGame();
}

int PuzzleSelectGameEngine::getCurrentIndex() {
	return curPuzzleIndex;
}