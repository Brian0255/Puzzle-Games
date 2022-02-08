#include "BattleshipEngine.h"
#include"QDifferentClicksButton.h"
#include"ColorConstants.h"
#include"ColorUtils.h"
#include"TileUtils.h"
#include<qregularexpression.h>
#include<random>

BattleshipEngine::BattleshipEngine(PuzzleGames* controller) : controller{ controller } {};

const int SHIP_START_AMOUNT{ 12 };
const int CLICK_START_AMOUNT{ 60 };
const int GRID_SIZE{ 10 };


BattleshipEngine::~BattleshipEngine() {
	for (auto& tileArray : tiles) {
		for (BattleshipTile tile : tileArray) {
			QPushButton* button = tile.button;
			delete button;
		}
	}
}

void BattleshipEngine::startEngine(){
	setupTiles();
	startGame();
}

void BattleshipEngine::setupTiles() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			QDifferentClicksButton* tileBtn = controller->createButton(i, j, false);
			tileBtn->setStyleSheet(
				"border: 0px;"
				"background-color: rgb(200,200,200);"
				"border-radius: 2px;"
				"font: 18pt \"Segoe UI Semilight\";"
				"color: rgb(255, 255, 255); "
			);
			tileBtn->setFixedSize(48, 48);
			tileBtn->installEventFilter(this);
			BattleshipTile tile = BattleshipTile(tileBtn);
			connect(tileBtn, &QDifferentClicksButton::leftClicked, this, &BattleshipEngine::tileButtonClick);
			connect(tileBtn, &QDifferentClicksButton::rightClicked, this, &BattleshipEngine::tileRightClick);
			std::array<int, 2> coords = { i,j };
			tiles[i][j] = tile;
			buttonCoords.insert({ tileBtn, coords });
		}
	}
}

void BattleshipEngine::startGame() {
	emit sendStatusLabelUpdate("");
	shipsRemaining = SHIP_START_AMOUNT;
	clicksLeft = CLICK_START_AMOUNT;
	emit sendTopLeftLabelUpdate("Ships left: " + QString::number(shipsRemaining));
	emit sendTopRightLabelUpdate("Clicks left: " + QString::number(clicksLeft));
	int max = tiles.size();
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::array<std::string, 4> orientations = { "horizontal","horizontal","vertical","vertical" };
	shuffle(shipLetters.begin(), shipLetters.end(), std::default_random_engine(seed));
	//shuffle ship letters so you can't deduce ship length/orientation from them
	for (int size : shipLengths) {
		for (std::string orientation : orientations) {
			createShip(orientation, size);
		}
	}
	setupTileShipCounts();
}

void BattleshipEngine::revealTile(QPushButton* button) {
	std::array<int, 2> coords = buttonCoords.at(button);
	int row = coords[0];
	int col = coords[1];
	tiles[row][col].reveal();
	ColorUtils::changeColor(button, ColorConstants::TILE_UNCOVERED_COLOR);
	if (tiles[row][col].isShip) {
		ColorUtils::changeColor(button, ColorConstants::HIT_PART_OF_SHIP_COLOR);
	}
	button->setEnabled(false);
	button->removeEventFilter(this);
	checkIfWin();
}

void BattleshipEngine::resetGame() {
	for (int i = 0; i < tiles.size(); ++i) {
		for (int j = 0; j < tiles.size(); ++j) {
			BattleshipTile* tile = &tiles[i][j];
			ColorUtils::changeColor(tile->button, ColorConstants::TILE_DEFAULT_COLOR);
			tile->button->installEventFilter(this);
			tile->button->setEnabled(true);
			tile->button->setText("");
			tile->hidden = true;
			tile->isShip = false;
			tile->crossedOff = false;
		}
	}
	ships.clear();
	startGame();
}

void BattleshipEngine::gameOver() {
	emit sendStatusLabelUpdate("Game over!");
	TileUtils::disableButtons(tiles);
}

void BattleshipEngine::checkIfWin() {
	calculateShipsRemaining();
	if (shipsRemaining == 0) {
		TileUtils::disableButtons(tiles);
		emit sendStatusLabelUpdate("You win!");
	}
}

void BattleshipEngine::tileRightClick() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	std::array<int, 2> coords = buttonCoords.at(button);
	BattleshipTile* tile = &tiles[coords[0]][coords[1]];
	if (tile->hidden) {
		if (!tile->crossedOff) {
			ColorUtils::changeColor(button, ColorConstants::BATTLESHIP_CROSS_OFF_COLOR);
			tile->crossedOff = true;
			button->removeEventFilter(this);
		}
		else {
			ColorUtils::changeColor(button, ColorConstants::TILE_DEFAULT_COLOR);
			tile->crossedOff = false;
			button->installEventFilter(this);
		}
	}
}

void BattleshipEngine::calculateShipsRemaining() {
	shipsRemaining = 0;
	for (BattleshipShip ship : ships) {
		shipsRemaining += (shipUncovered(ship)) ? 0 : 1;
	}
	emit sendTopLeftLabelUpdate("Ships left: " + QString::number(shipsRemaining));
}

bool BattleshipEngine::shipUncovered(BattleshipShip ship) {
	bool uncovered{ true };
	for (std::array coord : ship.coords) {
		int row = coord[0];
		int col = coord[1];
		if (tiles[row][col].hidden) {
			uncovered = false;
			break;
		}
	}
	if (uncovered) {
		for (std::array coord : ship.coords) {
			int row = coord[0];
			int col = coord[1];
			ColorUtils::changeColor(tiles[row][col].button, ColorConstants::HIT_SHIP_COLOR);
		}
	}
	return uncovered;
}

bool BattleshipEngine::checkIfShipFits(BattleshipShip ship) {
	bool fits{ true };
	for (std::array<int, 2> coord : ship.coords) {
		int row = coord[0];
		int col = coord[1];
		if (!tiles[row][col].hidden) {
			fits = false;
			break;
		}
	}
	return fits;
}

void BattleshipEngine::createShip(std::string orientation, int size) {
	if (orientation == "horizontal") {
		createHorizontalShip(size);
	}
	else if (orientation == "vertical") {
		createVerticalShip(size);
	}
}

void BattleshipEngine::createHorizontalShip(int size) {
	//horizontal will get built left to right
	int max = tiles.size();
	int limit = max - size + 1;
	bool valid{ false };
	while (!valid) {
		int row = rand() % limit;
		int col = rand() % max;
		BattleshipShip potentialShip;
		valid = true;
		for (int i = 0; i < size; ++i) {
			int newRow = row + i;
			int newCol = col;
			std::array<int, 2> coord = { newRow,newCol };
			potentialShip.coords.push_back(coord);
			if (tiles[newRow][newCol].isShip) {
				valid = false;
				break;
			}
		}
		if (valid) {
			addShip(potentialShip);
		}
	}
}

void BattleshipEngine::createVerticalShip(int size) {
	//vertical will get built top to bottom
	int max = tiles.size();
	int limit = max - size + 1;
	bool valid{ false };
	BattleshipShip ship;
	while (!valid) {
		int row = rand() % max;
		int col = rand() % limit;
		valid = true;
		BattleshipShip potentialShip;
		for (int i = 0; i < size; ++i) {
			int newRow = row;
			int newCol = col + i;
			std::array<int, 2> coord = { newRow,newCol };
			potentialShip.coords.push_back(coord);
			if (tiles[newRow][newCol].isShip) {
				valid = false;
				break;
			}
		}
		if (valid) {
			addShip(potentialShip);
		}
	}
}

void BattleshipEngine::addShip(BattleshipShip& potentialShip) {
	char letter = shipLetters[ships.size()];
	for (auto& coord : potentialShip.coords) {
		int row = coord[0];
		int col = coord[1];
		tiles[row][col].isShip = true;
		tiles[row][col].letter = letter;
	}
	ships.push_back(potentialShip);
}

void BattleshipEngine::tileButtonPress() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button->isEnabled())
		ColorUtils::changeColor(button, ColorConstants::TILE_PRESS_COLOR);
}

void BattleshipEngine::tileButtonClick() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (button->isEnabled()) {
		ColorUtils::changeColor(button, ColorConstants::TILE_UNCOVERED_COLOR);
		std::array<int, 2> coords = buttonCoords.at(button);
		BattleshipTile tile = tiles[coords[0]][coords[1]];
		--clicksLeft;
		emit sendTopRightLabelUpdate("Clicks left: " + QString::number(clicksLeft));
		revealTile(button);
		checkIfWin();
		if (clicksLeft == 0 && shipsRemaining > 0) {
			gameOver();
		}
	}
}


void BattleshipEngine::setupTileShipCounts() {
	int size = tiles.size();
	for (int i{ 0 }; i < size; ++i) {
		for (int j{ 0 }; j < size; ++j) {
			tiles[i][j].calculateShipsIntersecting(tiles, buttonCoords);
		}
	}
}
