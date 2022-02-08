#include "CoordinationEngine.h"
#include"ColorUtils.h"
#include"ColorConstants.h"
#include"CoordinationConstants.h"
#include"TileUtils.h"
#include"ArrayUtils.h"

const int GRID_SIZE{ 7 };
const int BUTTON_SIZE{ 40 };

CoordinationEngine::CoordinationEngine(PuzzleGames* controller)
	:controller{ controller },
	PuzzleSelectGameEngine(static_cast<int>(CoordinationConstants::layouts.size())) {};


CoordinationEngine::~CoordinationEngine() {
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			delete tile.button;
		}
	}
}

void CoordinationEngine::startEngine() {
	setupTiles();
	startGame();
}

void CoordinationEngine::startGame() {
	int curIndex = PuzzleSelectGameEngine::getCurrentIndex();
	currentLayout = CoordinationConstants::layouts[curIndex];
	putLayoutIntoTileGrid();
}

void CoordinationEngine::resetGame() {
	currentlyMoving = false;
	allBlockCoords.clear();
	startGame();
}

void CoordinationEngine::setupTiles() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			QDifferentClicksButton* tileBtn = controller->createButton(i, j, true);
			tileBtn->setStyleSheet(
				"border: 0px;"
				"background-color: rgb(200,200,200);"
				"border-radius: 2px;"
				"font: 14pt \"Segoe UI Semilight\";"
				"color: rgb(255, 255, 255); "
			);
			tileBtn->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
			tileBtn->installEventFilter(this);
			CoordinationTile tile = CoordinationTile();
			connect(tileBtn, &QDifferentClicksButton::leftClicked, this, &CoordinationEngine::tileButtonClick);
			std::array<int, 2> coords = { i,j };
			tiles[i][j] = tile;
			buttonCoords.insert({ tileBtn, coords });
		}
	}
}

void CoordinationEngine::putLayoutIntoTileGrid() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			CoordinationTile* tile = &tiles[i][j];
			char tileType = currentLayout.layout[i][j];
			switch (tileType) {
			case 'G':
				tile->tileType = GOAL;
				break;
			case 'X':
				tile->tileType = BARRIER;
				break;
			case 'B':
				tile->tileType = DEFAULT;
				tile->hasBlock = true;
				break;
			default:
				tile->tileType = DEFAULT;
				break;
			}
			tile->changeAppearance();
		}
	}
}


void CoordinationEngine::checkIfWin() {
	bool won{ true };
	for (auto& coords : allBlockCoords) {
		CoordinationTile tile = tiles[coords[0]][coords[1]];
		if (tile.tileType == GOAL) {
			won = false;
			break;
		}
	}
	if (won) {
		TileUtils::disableButtons(tiles);
		emit sendStatusLabelUpdate("You win!");
	}
}

void CoordinationEngine::tryToMoveOtherBlocks(std::array<int, 2> differenceToMove) {
}

void CoordinationEngine::moveBlock(std::array<int, 2> blockCoords, std::array<int, 2> differenceToMove) {
}

bool CoordinationEngine::coordInBounds(std::array<int, 2> coords) {
	int row = coords[0];
	int col = coords[1];
	bool validRow{ row >= 0 && row < tiles.size() };
	bool validCol{ col >= 0 && col < tiles[0].size() };
	return (validRow && validCol);
}

bool CoordinationEngine::isNeighboringCurrentTile(CoordinationTile* tile) {
	QPushButton* button = tile->button;
	std::array<int, 2> coordsChecking = buttonCoords.at(button);
	std::vector<std::array<int, 2>> differences{
		{0,1},{0,-1},{1,0},{-1,0}
	};
	for (std::array<int, 2> difference : differences) {
		std::array<int, 2> sum = ArrayUtils::addIntArrays(difference, activeBlockCoords);
		if ((sum == coordsChecking)) {
			return true;
		}
	}
	return false;
}

bool CoordinationEngine::eventFilter() {
	return false;
}

void CoordinationEngine::tileButtonClick() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	std::array<int, 2> coords = buttonCoords.at(button);
	CoordinationTile* tile = &tiles[coords[0]][coords[1]];
	if (tile->hasBlock) {
		if (!currentlyMoving) {
			activeBlockCoords = coords;
		}
		currentlyMoving = !currentlyMoving;
	}
}

void CoordinationEngine::coordBlockPress() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	ColorUtils::changeColor(button, ColorConstants::COORDINATION_BLOCK_PRESS_COLOR);
}

void CoordinationEngine::coordBlockRelease() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	ColorUtils::changeColor(button, ColorConstants::COORDINATION_BLOCK_HOVER_COLOR);
}
