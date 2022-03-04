#include "CoordinationEngine.h"
#include"ColorUtils.h"
#include"ColorConstants.h"
#include"CoordinationConstants.h"
#include"TileUtils.h"
#include"ArrayUtils.h"

const int GRID_SIZE{ 7 };
const int BUTTON_SIZE{ 72 };

CoordinationEngine::CoordinationEngine(PuzzleGames* controller)
	:controller{ controller }, currentlyMoving{ false },
	PuzzleSelectGameEngine(static_cast<int>(CoordinationConstants::layouts.size())) {};


CoordinationEngine::~CoordinationEngine() {
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			delete tile.button;
		}
	}
}

bool CoordinationEngine::startEngine() {
	if (controller != NULL) {
		setupTiles();
		startGame();
		return true;
	}
	return false;
}

void CoordinationEngine::startGame() {
	int curIndex = PuzzleSelectGameEngine::getCurrentIndex();
	currentLayout = CoordinationConstants::layouts[curIndex];
	putLayoutIntoTileGrid();
}

bool CoordinationEngine::resetGame() {
	if (tiles[0][0].button!=NULL) {
		emit sendStatusLabelUpdate("");
		currentlyMoving = false;
		allBlockCoords.clear();
		for (auto& tileArray : tiles) {
			for (auto& tile : tileArray) {
				tile.reset();
			}
		}
		TileUtils::enableButtons(tiles);
		startGame();
		return true;
	}
	return false;
}

void CoordinationEngine::setupTiles() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			QDifferentClicksButton* tileBtn = controller->createButton(i, j, true);
			tileBtn->setStyleSheet(
				"border: 0px;"
				"background-color: rgb(200,200,200);"
				"border-radius: 2px;"
				"font: 36pt \"Segoe UI Semilight\";"
				"color: rgb(75,106,198);"
			);
			tileBtn->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
			tileBtn->installEventFilter(this);
			CoordinationTile tile = CoordinationTile(tileBtn);
			connect(tileBtn, &QDifferentClicksButton::leftClicked, this, &CoordinationEngine::tileButtonClick);
			connect(tileBtn, &QDifferentClicksButton::leftReleased, this, &CoordinationEngine::tileButtonRelease);
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
				tile->tileType = COORD_TILE_TYPE::GOAL;
				break;
			case 'X':
				tile->tileType = COORD_TILE_TYPE::BARRIER;
				break;
			case 'B':
				tile->tileType = COORD_TILE_TYPE::DEFAULT;
				tile->hasBlock = true;
				allBlockCoords.push_back({ i,j });
				break;
			default:
				tile->tileType = COORD_TILE_TYPE::DEFAULT;
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
		if (tile.tileType != COORD_TILE_TYPE::GOAL) {
			won = false;
			break;
		}
	}
	if (won) {
		TileUtils::disableButtons(tiles);
		QPushButton* activeButton = tiles[activeBlockCoords[0]][activeBlockCoords[1]].button;
		ColorUtils::changeColor(activeButton, ColorConstants::COORDINATION_BLOCK_COLOR);
		emit sendStatusLabelUpdate("You win!");
	}
}

void CoordinationEngine::moveAllBlocks(std::array<int, 2> differenceToMove) {
	std::vector<std::array<int, 2>> oldCoords = allBlockCoords;
	std::vector<std::array<int, 2>> newCoords;
	for (auto& coord : allBlockCoords) {
		std::array<int, 2> newCoord = ArrayUtils::addIntArrays(coord, differenceToMove);
		newCoords.push_back((validSpotForBlock(newCoord)) ? newCoord : coord);
	} 
	std::array<int, 2> oldActiveCoords = activeBlockCoords;
	std::array<int, 2> newActiveCoords = ArrayUtils::addIntArrays(activeBlockCoords, differenceToMove);
	bool canMove = checkIfValidMove(differenceToMove);
	if (canMove) {
		activeBlockCoords = ArrayUtils::addIntArrays(activeBlockCoords, differenceToMove);
		clearOutOldBlockPositions();
		calculateNewBlockCoords(newCoords);
		setTilesToNewBlockCoords();
		//keep checking for overlap error until there is none
		while(checkForOverlapError(oldCoords, newCoords));
		CoordinationTile* activeTile = &tiles[activeBlockCoords[0]][activeBlockCoords[1]];
		ColorUtils::changeColor(activeTile->button, ColorConstants::COORDINATION_BLOCK_HOVER_COLOR);
		checkIfWin();
	}
}

bool CoordinationEngine::checkForOverlapError(std::vector<std::array<int, 2>>& oldCoords, std::vector<std::array<int, 2>>& newCoords) {
	for (int i = 0; i < oldCoords.size(); ++i) {
		if (allBlockCoords[i] != oldCoords[i]) {
			if (std::count(allBlockCoords.begin(), allBlockCoords.end(), allBlockCoords[i]) == 2) {
				allBlockCoords[i] = oldCoords[i];
				CoordinationTile* tile = &tiles[allBlockCoords[i][0]][allBlockCoords[i][1]];
				tile->hasBlock = true;
				tile->changeAppearance();
				return true;
			}
		}
	}
	return false;
}

void CoordinationEngine::setTilesToNewBlockCoords() {
	for (auto& coord : allBlockCoords) {
		CoordinationTile* tile = &tiles[coord[0]][coord[1]];
		tile->hasBlock = true;
		tile->changeAppearance();
	}
}

void CoordinationEngine::calculateNewBlockCoords(std::vector<std::array<int, 2>>& newCoords) {
	for (int i = 0; i < newCoords.size(); ++i) {
		if (std::count(newCoords.begin(), newCoords.end(), newCoords[i]) == 1) {
			allBlockCoords[i] = newCoords[i];
		}
	}
}

void CoordinationEngine::clearOutOldBlockPositions() {
	for (auto& coord : allBlockCoords) {
		int row = coord[0];
		int col = coord[1];
		tiles[row][col].hasBlock = false;
		tiles[row][col].changeAppearance();
	}
}

bool CoordinationEngine::checkIfValidMove(const std::array<int, 2>& differenceToMove) {
	bool canMove{ false };
	std::array<int, 2> nextCoord = ArrayUtils::addIntArrays(activeBlockCoords, differenceToMove);
	bool keepGoing{ true };
	while (keepGoing) {
		if (!coordInBounds(nextCoord)) {
			keepGoing = false;
			canMove = false;
			break;
		}
		CoordinationTile* tile = &tiles[nextCoord[0]][nextCoord[1]];
		if (validSpotForBlock(nextCoord) && !tile->hasBlock) {
			canMove = true;
			keepGoing = false;
			break;
		}
		else if (!validSpotForBlock(nextCoord)) {
			canMove = false;
			keepGoing = false;
			break;
		}
		nextCoord = ArrayUtils::addIntArrays(nextCoord, differenceToMove);
	}
	return canMove;
}

void CoordinationEngine::moveBlock(int i, std::vector<std::array<int,2>>& newCoords) {
	std::array<int, 2>& coord = allBlockCoords[i];
	if (std::find(newCoords.begin(), newCoords.end(), coord) == newCoords.end()) {
		allBlockCoords[i] = newCoords[i];
	}
	int row = allBlockCoords[i][0];
	int col = allBlockCoords[i][1];
	tiles[row][col].hasBlock = true;
	tiles[row][col].changeAppearance();
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

bool CoordinationEngine::validSpotForBlock(std::array<int, 2> coords) {
	if (coordInBounds(coords)) {
		CoordinationTile* tile = &tiles[coords[0]][coords[1]];
		bool validType{ tile->tileType == COORD_TILE_TYPE::DEFAULT || tile->tileType == COORD_TILE_TYPE::GOAL};
		return validType;
	}
	return false;
}

bool CoordinationEngine::eventFilter(QObject* watched, QEvent* event) {
	QPushButton* btn = static_cast<QPushButton*>(watched);
	std::array<int, 2> coords = buttonCoords.at(btn);
	CoordinationTile* tile = &tiles[coords[0]][coords[1]];
	bool onBlock{ std::find(allBlockCoords.begin(),allBlockCoords.end(),coords) != allBlockCoords.end() };
	if (btn && btn->isEnabled()) {
		if (event->type() == QEvent::Enter){
			if (!currentlyMoving && onBlock) {
				ColorUtils::changeColor(btn, ColorConstants::COORDINATION_BLOCK_HOVER_COLOR);
			}
			else if (currentlyMoving) {
				if (isNeighboringCurrentTile(tile)) {
					if (tile->tileType == COORD_TILE_TYPE::DEFAULT || tile->tileType == COORD_TILE_TYPE::GOAL) {
						std::array<int, 2> difference = ArrayUtils::subtractIntArrays(coords, activeBlockCoords);
						moveAllBlocks(difference);
					}
				}
			}
		}

		else if (event->type() == QEvent::Leave && !currentlyMoving && onBlock){
			ColorUtils::changeColor(btn, ColorConstants::COORDINATION_BLOCK_COLOR);
		}
	}

	return QObject::eventFilter(watched, event);
}

void CoordinationEngine::tileButtonClick() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	std::array<int, 2> coords = buttonCoords.at(button);
	CoordinationTile* tile = &tiles[coords[0]][coords[1]];
	if (tile->hasBlock) {
		if (currentlyMoving && button == tiles[activeBlockCoords[0]][activeBlockCoords[1]].button) {
			ColorUtils::changeColor(button, ColorConstants::COORDINATION_BLOCK_PRESS_COLOR);
		}
		else if(!currentlyMoving){
			ColorUtils::changeColor(button, ColorConstants::COORDINATION_BLOCK_PRESS_COLOR);
		}
	}

}

void CoordinationEngine::tileButtonRelease() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	std::array<int, 2> coords = buttonCoords.at(button);
	CoordinationTile* tile = &tiles[coords[0]][coords[1]];
	if (tile->hasBlock) {
		if (!currentlyMoving) {
			activeBlockCoords = coords;
			currentlyMoving = true;
			ColorUtils::changeColor(button, ColorConstants::COORDINATION_BLOCK_HOVER_COLOR);
		}
		else if (currentlyMoving && button == tiles[activeBlockCoords[0]][activeBlockCoords[1]].button) {
			currentlyMoving = false;
			ColorUtils::changeColor(button, ColorConstants::COORDINATION_BLOCK_COLOR);
		}
	}
}
