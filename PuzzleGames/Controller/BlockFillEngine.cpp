#include "BlockFillEngine.h"
#include"BlockFillConstants.h"
#include"ColorUtils.h"
#include"ArrayUtils.h"
#include"TileUtils.h"
#include"ColorConstants.h"

const int GRID_SIZE = 16;
const int BUTTON_SIZE = 30;

BlockFillEngine::BlockFillEngine(PuzzleGames* controller)
	: PuzzleSelectGameEngine(static_cast<int>(BlockFillConstants::layouts.size())),
		controller{ controller }, dragging{ false }  {};

BlockFillEngine::~BlockFillEngine() {
	for (BlockFillShape* shape : shapes) {
		delete shape;
	}
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			delete tile.button;
		}
	}
}

void BlockFillEngine::startEngine() {
	controller->changePuzzleGridSpacing(2);
	setupTiles();
	startGame();
}

void BlockFillEngine::startGame() {
	putLayoutIntoTileGrid();
}

void BlockFillEngine::resetTiles() {
	for(auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			tile.reset();
		}
	}
}

void BlockFillEngine::resetGame() {
	for (BlockFillShape* shape : shapes) {
		delete shape;
	}
	TileUtils::enableButtons(tiles);
	shapes.clear();
	resetTiles();
	dragging = false;
	currentShape = NULL;
	emit sendStatusLabelUpdate("");
	startGame();
}

void BlockFillEngine::checkIfWin() {
	bool win{ true };
	for (BlockFillShape* shape : shapes) {
		for (auto& coord : shape->coords) {
			BlockFillTile tile = tiles[coord[0]][coord[1]];
			if (!tile.goal) {
				win = false;
				break;
			}
		}
	}
	if (win) {
		emit sendStatusLabelUpdate("You win!");
		for (auto& shape : shapes) {
			unhighlightShape(shape);
		}
		TileUtils::disableButtons(tiles);
	}
}

void BlockFillEngine::putLayoutIntoTileGrid() {
	int curIndex = PuzzleSelectGameEngine::getCurrentIndex();
	GameLayout<16> currentLayout = BlockFillConstants::layouts[curIndex];
	std::array<std::string, 16> layout = currentLayout.layout;
	for (int i = 0; i < layout.size(); ++i) {
		for (int j = 0; j < layout[0].size(); ++j) {
			QChar charAt = layout[i][j];
			if (charAt == 'G') {
				BlockFillTile* tile = &tiles[i][j];
				tile->goal = true;
				ColorUtils::changeColor(tile->button, ColorConstants::BLOCK_FILL_GOAL_TILE_COLOR);
			}
			else if (charAt == 'B') {
				BlockFillTile* tile = &tiles[i][j];
				tile->barrier = true;
				ColorUtils::changeColor(tile->button, ColorConstants::BLOCK_FILL_BARRIER_COLOR);
			}
			else {
				std::array<QChar, 7> pieceNames = BlockFillConstants::pieceNames;
				if (std::find(pieceNames.begin(), pieceNames.end(), charAt) != pieceNames.end()) {
					createShape(currentLayout, i, j);
				}
			}
		}
	}
}

void BlockFillEngine::createShape(GameLayout<GRID_SIZE> layout, int row, int col) {
	int rowSize = layout.layout[0].size();
	int totalRows = layout.layout.size();
	QChar shapeType = layout.layout[row][col];
	QChar name = layout.layout[row][col + 1];
	BlockFillShape* shape = new BlockFillShape(name, shapeType);
	//look for every other instance of the name in the layout, add to shape coords
	for (int i = col+1; i < rowSize; ++i) {
		QChar charAt = layout.layout[row][i];
		if (charAt == name) {
			shape->coords.push_back({ row,i });
		}
	}
	for (int i = row + 1; i < totalRows; ++i) {
		for (int j = 0; j < rowSize; ++j) {
			QChar charAt = layout.layout[i][j];
			if (charAt == name) {
				shape->coords.push_back({ i,j });
			}
		}
	}
	shape->currentAnchorPoint = shape->coords[3];
	connectShapeWithTiles(shape);
	shapes.push_back(shape);
}

void BlockFillEngine::connectShapeWithTiles(BlockFillShape* shape) {
	for (auto& coord : shape->coords) {
		int row = coord[0];
		int col = coord[1];
		BlockFillTile* tile = &tiles[row][col];
		tile->shape = shape;
		changeTileColorToShape(tile);
	}
}

void BlockFillEngine::changeTileColorToShape(BlockFillTile* tile) {
	QChar shapeType = tile->shape->shapeType;
	QString color = ColorConstants::BLOCK_FILL_PIECE_COLORS.at(shapeType);
	ColorUtils::changeColor(tile->button, color);
}

void BlockFillEngine::clearCurrentShapeColors() {
	for (auto& coord : currentShape->coords) {
		int row = coord[0];
		int col = coord[1];
		bool validRow{ row < GRID_SIZE&& row >= 0 };
		bool validCol{ col < GRID_SIZE&& col >= 0 };
		if (validRow && validCol) {
			BlockFillTile* tile = &tiles[row][col];
			tile->button->setText("");
			if (tile->barrier) {
				ColorUtils::changeColor(tile->button, ColorConstants::BLOCK_FILL_BARRIER_COLOR);
			}
			else if (tile->shape != NULL) {
				changeTileColorToShape(tile);
			}
			else if (tile->goal) {
				ColorUtils::changeColor(tile->button, ColorConstants::BLOCK_FILL_GOAL_TILE_COLOR);
			}
			else {
				ColorUtils::changeColor(tile->button, ColorConstants::BLOCK_FILL_DEFAULT_TILE_COLOR);
			}
		}
	}
}

void BlockFillEngine::fillCurrentShapeColors() {
	for (auto& coord : currentShape->coords) {
		int row = coord[0];
		int col = coord[1];
		bool validRow{ row < GRID_SIZE && row >= 0 };
		bool validCol{ col < GRID_SIZE && col >= 0 };
		if (validRow && validCol) {
			BlockFillTile* tile = &tiles[row][col];
			QString color = ColorConstants::BLOCK_FILL_PIECE_HIGHLIGHT_COLORS.at(currentShape->shapeType);
			if (currentShape->inValidSpot() && !overlapAtCurrentSpot()) {
				ColorUtils::changeColor(tile->button, color);
			}
			else {
				ColorUtils::changeColor(tile->button, ColorConstants::BLOCK_FILL_OVERLAP_ERROR_COLOR);
				tile->button->setText("X");
			}
		}
	}
}

bool BlockFillEngine::overlapAtCurrentSpot() {
	for (auto& coord : currentShape->coords) {
		BlockFillTile tile = tiles[coord[0]][coord[1]];
		if (tile.shape != NULL || tile.barrier) {
			return true;
		}
	}
	return false;
}

void BlockFillEngine::highlightShape(BlockFillShape* shape) {
	QString color = ColorConstants::BLOCK_FILL_PIECE_HIGHLIGHT_COLORS.at(shape->shapeType);
	for (auto& coord : shape->coords) {
		ColorUtils::changeColor(tiles[coord[0]][coord[1]].button, color);
	}
}

void BlockFillEngine::unhighlightShape(BlockFillShape* shape) {
	QString color = ColorConstants::BLOCK_FILL_PIECE_COLORS.at(shape->shapeType);
	for (auto& coord : shape->coords) {
		ColorUtils::changeColor(tiles[coord[0]][coord[1]].button, color);
	}
}

bool BlockFillEngine::eventFilter(QObject* watched, QEvent* event) {
	QFrame* frame = static_cast<QFrame*>(watched);
	if (frame->objectName()=="BlockFillTileFrame") {
		handleFrameEventFilter(event);
	}
	else {
		QPushButton* btn = static_cast<QPushButton*>(watched);
		if (btn && btn->isEnabled()) {
			handleButtonEventFilter(event, btn);
		}
	}
	return QObject::eventFilter(watched, event);
}

void BlockFillEngine::handleButtonEventFilter(QEvent* event, QPushButton*& btn) {
	std::array<int, 2> coords = buttonCoords.at(btn);
	int row = coords[0];
	int col = coords[1];
	BlockFillTile* tile = &tiles[row][col];
	if (event->type() == QEvent::Enter) {
		if (dragging) {
			std::array<int, 2> newCoords = buttonCoords.at(btn);
			std::array<int, 2> difference = ArrayUtils::subtractIntArrays(newCoords, lastMouseGridPosition);
			clearCurrentShapeColors();
			currentShape->move(difference);
			fillCurrentShapeColors();
			lastMouseGridPosition = newCoords;
		}
		else {
			if (tile->shape != NULL) {
				highlightShape(tile->shape);
			}
		}
	}

	else if (event->type() == QEvent::Leave) {
		if (tile->shape != NULL && !dragging) {
			unhighlightShape(tile->shape);
		}
	}
}

void BlockFillEngine::handleFrameEventFilter(QEvent* event) {
	if (event->type() == QEvent::MouseButtonPress) {
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->button() == Qt::RightButton) {
			if (dragging) {
				clearCurrentShapeColors();
				currentShape->rotateRight();
				fillCurrentShapeColors();
			}
		}
	}
}

void BlockFillEngine::tileBtnClick() {

	QPushButton* button = qobject_cast<QPushButton*>(sender());
	std::array<int, 2> coords = buttonCoords.at(button);
	BlockFillTile* tile = &tiles[coords[0]][coords[1]];
	if (tile->shape != NULL && !dragging){
		setupShapeDrag(tile, button);
	}
	else if (dragging && currentShape->inValidSpot()&&!overlapAtCurrentSpot()) {
		placeCurrentBlock();
		checkIfWin();
	}
}

void BlockFillEngine::placeCurrentBlock() {
	dragging = false;
	for (auto& coord : currentShape->coords) {
		int row = coord[0];
		int col = coord[1];
		tiles[row][col].shape = currentShape;
	}
	currentShape = NULL;
}

void BlockFillEngine::tileBtnRightClick() {
	if (dragging) {
		clearCurrentShapeColors();
		currentShape->rotateRight();
		fillCurrentShapeColors();
	}
}

void BlockFillEngine::setupShapeDrag(BlockFillTile* tile, QPushButton*& button) {
	BlockFillShape* tileShape = tile->shape;
	dragging = true;
	currentShape = tileShape;
	std::array<int, 2> coords = buttonCoords.at(button);
	for (std::array<int, 2> shapeCoord : currentShape->coords) {
		tiles[shapeCoord[0]][shapeCoord[1]].shape = NULL;
		if (shapeCoord == coords) {
			currentShape->currentAnchorPoint = coords;
			lastMouseGridPosition = coords;
		}
	}
}

void BlockFillEngine::setupTiles() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			QDifferentClicksButton* tileBtn = controller->createButton(i, j, true);
			tileBtn->setStyleSheet(
				"border: 0px;"
				"background-color: rgb(160,160,160);"
				"font: 16pt \"Segoe UI Semilight\";"
				"color: rgb(222, 80, 80); "
			);
			tileBtn->setFixedSize(BUTTON_SIZE, BUTTON_SIZE);
			tileBtn->installEventFilter(this);
			BlockFillTile tile = BlockFillTile(tileBtn);
			tile.barrier = false;
			connect(tileBtn, &QDifferentClicksButton::leftClicked, this, &BlockFillEngine::tileBtnClick);
			connect(tileBtn, &QDifferentClicksButton::rightClicked, this, &BlockFillEngine::tileBtnRightClick);
			std::array<int, 2> coords = { i,j };
			tiles[i][j] = tile;
			buttonCoords.insert({ tileBtn, coords });
		}
	}
}


