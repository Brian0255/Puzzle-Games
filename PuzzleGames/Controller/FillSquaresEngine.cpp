#include "FillSquaresEngine.h"
#include"Utilities.h"
#include"ColorConstants.h"
#include"FillSquareConstants.h"
#include<vector>

const int GRID_SIZE{ 8 };
FillSquaresEngine::FillSquaresEngine(PuzzleGames* controller) : controller{ controller } {
	srand(time(0));
	currentLayout.layout = {};
}

FillSquaresEngine::~FillSquaresEngine() {
	for (auto& tileArray : tiles) {
		for (FillSquaresTile tile : tileArray) {
			QPushButton* button = tile.button;
			delete button;
		}
	}
}
;

void FillSquaresEngine::startEngine() {
	setupTiles();
	startGame();
}

void FillSquaresEngine::resetGame() {
	resetTiles();
	startGame();
	emit sendStatusLabelUpdate("");
}

void FillSquaresEngine::resetTiles() {
	buttonFillSequence.clear();
	currentlyFilling = false;
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			tile.filled = false;
			tile.XSpot = false;
			tile.button->setEnabled(true);
			Utilities::changeColor(tile.button, ColorConstants::TILE_DEFAULT_COLOR);
		}
	}
}

void FillSquaresEngine::rotateLayoutRandomly(FillSquareLayout& layout) {
	for (int i = 0; i < (rand() % 4); ++i) {
		transposeLayout(layout);
		rotate90Degrees(layout);
	}
}

void FillSquaresEngine::transposeLayout(FillSquareLayout& layout) {
	for (int i = 0; i < GRID_SIZE; i += 1) {
		for (int j = i + 1; j < GRID_SIZE; j += 1) {
			char temp = layout.layout[i][j];
			layout.layout[i][j] = layout.layout[j][i];
			layout.layout[j][i] = temp;
		}
	}
}

void FillSquaresEngine::rotate90Degrees(FillSquareLayout& layout) {
	for (std::string row : layout.layout){
		std::reverse(row.begin(), row.end());
	}
}



void FillSquaresEngine::updateColors() {
	QPushButton* lastFilled = NULL;
	QPushButton* filledBeforeLast = NULL;
	if (buttonFillSequence.size() > 0) {
		lastFilled = buttonFillSequence.at(buttonFillSequence.size() - 1);
		Utilities::changeColor(lastFilled, ColorConstants::FILL_SQUARES_HEAD_COLOR);
	}
	if (buttonFillSequence.size() > 1) {
		filledBeforeLast = buttonFillSequence.at(buttonFillSequence.size() - 2);
		Utilities::changeColor(filledBeforeLast, ColorConstants::FILL_SQUARES_BEFORE_HEAD_COLOR);
	}
	if (buttonFillSequence.size() > 2) {
		for (int i = 0; i < (buttonFillSequence.size() - 2); ++i) {
			Utilities::changeColor(buttonFillSequence[i], ColorConstants::FILL_SQUARES_FILL_COLOR);
		}
	}
	checkIfWin();
}

bool FillSquaresEngine::eventFilter(QObject* watched, QEvent* event) {
	QPushButton* btn = static_cast<QPushButton*>(watched);
	QPushButton* lastFilled = NULL;
	QPushButton* filledBeforeLast = NULL;
	std::array<int, 2> coords = buttonCoords.at(btn);
	FillSquaresTile* tile = &tiles[coords[0]][coords[1]];
	bool activeButton{ !tile->filled };
	if (buttonFillSequence.size() > 0) {
		lastFilled = buttonFillSequence.at(buttonFillSequence.size() - 1);
	}
	if (buttonFillSequence.size() > 1) {
		filledBeforeLast = buttonFillSequence.at(buttonFillSequence.size() - 2);
	}
	if (btn && btn->isEnabled() && !tile->XSpot) {
		if (event->type() == QEvent::Enter) {
			if (lastFilled!=NULL && isNeighboringCurrentTile(tile)) {
				goForward(lastFilled, tile, btn);
			}
			else if (filledBeforeLast!=NULL && btn == filledBeforeLast) {
				goBackwards(lastFilled, btn);
			}
			else if(activeButton){
				Utilities::changeColor(btn, ColorConstants::TILE_HOVER_COLOR);
			}
			updateColors();
		}

		else if (event->type() == QEvent::Leave && activeButton) {
			Utilities::changeColor(btn, ColorConstants::TILE_DEFAULT_COLOR);
		}
	}

	return QObject::eventFilter(watched, event);
}

void FillSquaresEngine::goForward(QPushButton*& lastFilled, FillSquaresTile* tile, QPushButton*& btn) {
	std::array<int, 2> coordsCurrent = buttonCoords.at(lastFilled);
	FillSquaresTile* curTile = &tiles[coordsCurrent[0]][coordsCurrent[1]];
	tile->fill();
	buttonFillSequence.push_back(btn);
}

void FillSquaresEngine::goBackwards(QPushButton*& lastFilled, QPushButton* btn) {
	std::array<int, 2> coords = buttonCoords.at(lastFilled);
	FillSquaresTile* curTile = &tiles[coords[0]][coords[1]];
	curTile->reset();
	buttonFillSequence.pop_back();
	Utilities::changeColor(btn, ColorConstants::FILL_SQUARES_HEAD_COLOR);
}

void FillSquaresEngine::setupTiles() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			QDifferentClicksButton* tileBtn = controller->createFillSquaresButton(i, j);
			tileBtn->setStyleSheet(
				"border: 0px;"
				"background-color: rgb(200,200,200);"
				"border-radius: 2px;"
				"font: 18pt \"Segoe UI Semilight\";"
				"color: rgb(255, 255, 255); "
			);
			tileBtn->setFixedSize(60, 60);
			tileBtn->installEventFilter(this);
			FillSquaresTile tile = FillSquaresTile(tileBtn);
			connect(tileBtn, &QDifferentClicksButton::leftClicked, this, &FillSquaresEngine::tileButtonClick);
			connect(tileBtn, &QDifferentClicksButton::rightClicked, this, &FillSquaresEngine::tileRightClick);
			std::array<int, 2> coords = { i,j };
			tiles[i][j] = tile;
			buttonCoords.insert({ tileBtn, coords });
		}
	}
}

void FillSquaresEngine::resetFill() {
	buttonFillSequence.clear();
	currentlyFilling = false;
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			FillSquaresTile* tile = &tiles[i][j];
			tile->reset();
		}
	}
}

void FillSquaresEngine::checkIfWin() {
	bool won{ true };
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			if (!tile.filled && !tile.XSpot) {
				won = false;
				break;
			}
		}
	}
	if (won) {
		emit sendStatusLabelUpdate("You win!");
		Utilities::changeColor(buttonFillSequence.at(buttonFillSequence.size() - 1), ColorConstants::FILL_SQUARES_FILL_COLOR);
		Utilities::changeColor(buttonFillSequence.at(buttonFillSequence.size() - 2), ColorConstants::FILL_SQUARES_FILL_COLOR);
		disableButtons();
	}
}

void FillSquaresEngine::disableButtons() {
	for (std::array<FillSquaresTile, 8> tileRow : tiles) {
		for (FillSquaresTile tile : tileRow) {
			tile.button->setEnabled(false);
		}
	}
}

void FillSquaresEngine::startGame() {
	std::vector<FillSquareLayout> layouts = FillSquareConstants::layouts;
	FillSquareLayout layout;
	do {
		int randIndex = rand() % layouts.size();
		layout = layouts[randIndex];
	} while (layout.layout == currentLayout.layout);
	currentLayout = layout;
	rotateLayoutRandomly(layout);
	putLayoutIntoTileGrid(layout);
}

void FillSquaresEngine::putLayoutIntoTileGrid(FillSquareLayout layout) {
	std::array<std::string, 8> rows = layout.layout;
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			char letter = rows[i][j];
			qDebug() << letter;
			if (letter == 'X') {
				setTileAsBlockedOff(i, j);
			}
		}
	}
}

void FillSquaresEngine::setTileAsBlockedOff(int i, int j) {
	FillSquaresTile* tile = &tiles[i][j];
	tile->XSpot = true;
	Utilities::changeColor(tile->button, ColorConstants::FILL_SQUARES_X_COLOR);
}

bool FillSquaresEngine::isNeighboringCurrentTile(FillSquaresTile* tile) {
	QPushButton* lastFilledButton = buttonFillSequence.at(buttonFillSequence.size() - 1);
	QPushButton* button = tile->button;
	std::array<int, 2> coordsChecking = buttonCoords.at(button);
	std::array<int, 2> coordsCurrent = buttonCoords.at(lastFilledButton);
	std::vector<std::array<int, 2>> differences{
		{0,1},{0,-1},{1,0},{-1,0}
	};
	for (std::array<int, 2> difference : differences) {
		std::array<int, 2> sum = {
			difference[0] + coordsCurrent[0],
			difference[1] + coordsCurrent[1]
		};
		if ((sum[0] == coordsChecking[0]) && (sum[1] == coordsChecking[1])&&!tile->filled) {
			return true;
		}
	}
	return false;
}

void FillSquaresEngine::tileButtonPress() {
}

void FillSquaresEngine::tileButtonClick() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	std::array<int, 2> coords = buttonCoords.at(button);
	FillSquaresTile* tile = &tiles[coords[0]][coords[1]];
	if (!tile->XSpot) {
		if (!currentlyFilling) {
			currentlyFilling = true;
			buttonFillSequence.push_back(button);
			tile->fill();
			updateColors();
		}
	}
}

void FillSquaresEngine::tileRightClick() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	resetFill();
	if (Utilities::getColor(button) != ColorConstants::FILL_SQUARES_X_COLOR) {
		Utilities::changeColor(button, ColorConstants::TILE_HOVER_COLOR);
	}
}
