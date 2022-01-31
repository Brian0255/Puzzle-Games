#include "BlockSlideEngine.h"
#include"Utilities.h"
#include"ColorConstants.h"
#include"BlockSlideConstants.h"
#include<qpropertyanimation.h>
#include<qsequentialanimationgroup.h>

const int GRID_SIZE{ 6 };
const int GRID_SPACING{ 4 };
const int BUTTON_SIZE{ 92 };

BlockSlideEngine::BlockSlideEngine(PuzzleGames* controller)
	:controller{ controller } {
		currentSelectedBlock = new SlidingBlock();
};

BlockSlideEngine::~BlockSlideEngine() {
	for (SlidingBlock* block : slidingBlocks) {
		delete block->button;
		delete block;
	}
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			delete tile.button;
		}
	}
}

void BlockSlideEngine::setupTiles() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			QDifferentClicksButton* tileBtn = controller->createBlockSlideButton(i, j);
			tileBtn->setStyleSheet(
				"border: 0px;"
				"background-color: rgb(160,160,160);"
				"font: 40pt \"Segoe UI Semilight\";"
				"color: rgb(222, 80, 80); "
			);
			tileBtn->setFixedSize(92, 92);
			BlockSlideTile tile = BlockSlideTile(tileBtn);
			tile.barrier = false;
			connect(tileBtn, &QDifferentClicksButton::leftClicked, this, &BlockSlideEngine::tileBtnClick);
			std::array<int, 2> coords = { i,j };
			tiles[i][j] = tile;
			buttonCoords.insert({ tileBtn, coords });
		}
	}
}

void BlockSlideEngine::checkIfWin() {
	int goalsHit{ 0 };
	for (auto& block : slidingBlocks) {
		std::array<int, 2> coords = block->coords;
		BlockSlideTile tile = tiles[coords[0]][coords[1]];
		goalsHit += (tile.goal) ? 1 : 0;
	}
	if (goalsHit == numGoals) {
		emit sendStatusLabelUpdate("You win!");
		disableButtons();
	}
}

void BlockSlideEngine::startEngine() {
	setupTiles();
	startGame();
}

void BlockSlideEngine::resetGame() {
	if (!animationActive) {
		emit sendStatusLabelUpdate("");
		for (SlidingBlock* block : slidingBlocks) {
			delete block->button;
			delete block;
		}
		for (auto& tileArray : tiles) {
			for (auto& tile : tileArray) {
				tile.reset();
			}
		}
		slidingBlocks.clear();
		enableButtons();
		startGame();
	}
}

void BlockSlideEngine::startGame() {
	if (resetOnlyThePuzzle) {
		putLayoutIntoTileGrid();
	}
	else {
		currentLayout = BlockSlideConstants::layouts[0];
		putLayoutIntoTileGrid();
	}
}

void BlockSlideEngine::disableButtons() {
	for (SlidingBlock* block : slidingBlocks) {
		block->button->setEnabled(false);
		block->button->removeEventFilter(this);
	}
	for (auto& tileArray : tiles) {
		for (BlockSlideTile tile : tileArray) {
			tile.button->setEnabled(false);
		}
	}
}

void BlockSlideEngine::enableButtons() {
	for (SlidingBlock* block : slidingBlocks) {
		block->button->setEnabled(true);
		block->button->installEventFilter(this);
	}
	for (auto& tileArray : tiles) {
		for (BlockSlideTile tile : tileArray) {
			tile.button->setEnabled(true);
		}
	}
}

void BlockSlideEngine::createSlidingBlock(int row, int col) {
	SlidingBlock* block = new SlidingBlock();
	controller->setupSlidingBlock(*block, 0,0);
	block->coords = { row,col };
	tiles[row][col].barrier = true;
	QDifferentClicksButton* button = block->button;
	button->setStyleSheet(
		"border: 0px;"
		"background-color: rgb(160,160,160);"
		"font: 60pt \"Segoe UI Semilight\";"
		"color: rgb(240, 104, 104); "
	);
	Utilities::changeColor(button, ColorConstants::BLOCK_SLIDE_BLOCK_COLOR);
	button->setFixedSize(92, 92);
	int xOffset = (col * (GRID_SPACING + BUTTON_SIZE));
	int yOffset = (row * (GRID_SPACING + BUTTON_SIZE));
	button->move(GRID_SPACING + xOffset, GRID_SPACING + yOffset);
	button->show();
	connect(button, &QDifferentClicksButton::leftClicked, this, &BlockSlideEngine::slidingBlockBtnClick);
	connect(button, &QDifferentClicksButton::rightClicked, this, &BlockSlideEngine::slidingBlockBtnRightClick);
	button->installEventFilter(this);
	currentSelectedBlock = block;
	slidingBlocks.push_back(block);
}

void BlockSlideEngine::highlightPossibleMoves(SlidingBlock* block) {
	highlightToTheRight(block);
	highlightToTheLeft(block);
	highlightAbove(block);
	highlightBelow(block);
	BlockSlideTile* tile = &tiles[block->coords[0]][block->coords[1]];
	tile->clearHighlight();
}

void BlockSlideEngine::highlightToTheRight(SlidingBlock* block) {
	std::array<int, 2> coords = block->coords;
	int row = coords[0];
	int col = coords[1];
	bool foundMatch{ false };
	for (int i = col + 1; i < GRID_SIZE; ++i) {
		BlockSlideTile* tile = &tiles[row][i];
		if (tile->barrier) {
			//barrier was found, highlight 
			tiles[row][i - 1].highlight();
			foundMatch = true;
			break;
		}
	}
	if (!foundMatch) {
		//no match found must mean the wall is what should be highlighted
		tiles[row][GRID_SIZE - 1].highlight();
	}
}

void BlockSlideEngine::highlightToTheLeft(SlidingBlock* block) {
	std::array<int, 2> coords = block->coords;
	int row = coords[0];
	int col = coords[1];
	bool foundMatch{ false };
	for (int i = col - 1; i >= 0; --i) {
		BlockSlideTile* tile = &tiles[row][i];
		if (tile->barrier) {
			tiles[row][i + 1].highlight();
			foundMatch = true;
			break;
		}
	}
	if (!foundMatch) {
		tiles[row][0].highlight();
	}
}

void BlockSlideEngine::highlightAbove(SlidingBlock* block) {
	std::array<int, 2> coords = block->coords;
	int row = coords[0];
	int col = coords[1];
	bool foundMatch{ false };
	for (int i = row - 1; i >= 0; --i) {
		BlockSlideTile* tile = &tiles[i][col];
		if (tile->barrier) {
			tiles[i+1][col].highlight();
			foundMatch = true;
			break;
		}
	}
	if (!foundMatch) {
		tiles[0][col].highlight();
	}
}

void BlockSlideEngine::highlightBelow(SlidingBlock* block) {
	std::array<int, 2> coords = block->coords;
	int row = coords[0];
	int col = coords[1];
	bool foundMatch{ false };
	for (int i = row + 1; i < GRID_SIZE; ++i) {
		BlockSlideTile* tile = &tiles[i][col];
		if (tile->barrier) {
			tiles[i-1][col].highlight();
			foundMatch = true;
			break;
		}
	}
	if (!foundMatch) {
		tiles[GRID_SIZE-1][col].highlight();
	}
}

void BlockSlideEngine::clearHighlights() {
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			tile.clearHighlight();
		}
	}
}

void BlockSlideEngine::moveCurrentBlock(std::array<int, 2> newCoords) {
	std::array<int,2> blockCoords = currentSelectedBlock->coords;
	tiles[blockCoords[0]][blockCoords[1]].barrier = false;
	tiles[newCoords[0]][newCoords[1]].barrier = true;
	clearHighlights();
	moveSmoothly(newCoords);
	currentSelectedBlock->coords = newCoords;
	currentSelectedBlock->button->show();
	updateBlock();
}

void BlockSlideEngine::moveSmoothly(std::array<int, 2> newCoords) {
	QPushButton* button = currentSelectedBlock->button;
	std::array<int, 2> blockCoords = currentSelectedBlock->coords;
	std::array<int, 2> difference = {
		newCoords[0] - blockCoords[0],
		newCoords[1] - blockCoords[1]
	};
	int xOffset = difference[1] * (GRID_SPACING + BUTTON_SIZE);
	int yOffset = difference[0] * (GRID_SPACING + BUTTON_SIZE);

	QSequentialAnimationGroup* group = new QSequentialAnimationGroup(this);
	QPropertyAnimation* anim = new QPropertyAnimation(button, "geometry");
	QRect geometry = button->geometry();
	anim->setDuration(std::abs(difference[0]+difference[1]) * 150);
	anim->setStartValue(geometry);
	anim->setEndValue(geometry.translated(xOffset, yOffset));
	group->addAnimation(anim);
	group->start();
	animationActive = true;
	disableButtons();
	connect(anim, &QPropertyAnimation::finished, this, &BlockSlideEngine::animationFinished);
}

void BlockSlideEngine::updateBlock() {
	for (SlidingBlock* block : slidingBlocks) {
		if (block->button == currentSelectedBlock->button) {
			block->coords = currentSelectedBlock->coords;
			break;
		}
	}
}

void BlockSlideEngine::putLayoutIntoTileGrid() {
	numGoals = 0;
	for (int i = 0; i < currentLayout.layout.size(); ++i) {
		for (int j = 0; j < currentLayout.layout[0].size(); ++j) {
			char letter = currentLayout.layout[i][j];
			switch (letter) {
			case 'B':
				createSlidingBlock(i, j);
				break;
			case 'X':
				setTileAsBarrier(i, j);
				break;
			case 'O':
				setTileAsGoal(i, j);
				++numGoals;
				break;
			default:
				break;
			}
		}
	}
}

void BlockSlideEngine::setTileAsBarrier(int i, int j) {
	BlockSlideTile* tile = &tiles[i][j];
	tile->barrier = true;
	Utilities::changeColor(tile->button, ColorConstants::BLOCK_SLIDE_BARRIER_COLOR);
}

void BlockSlideEngine::setTileAsGoal(int i, int j) {
	BlockSlideTile* tile = &tiles[i][j];
	tile->goal = true;
	tile->button->setText("X");
}

bool BlockSlideEngine::eventFilter(QObject* watched, QEvent* event) {
	QPushButton* btn = static_cast<QPushButton*>(watched);
	if (btn && btn->isEnabled()) {
		if (event->type() == QEvent::Enter) {
			Utilities::changeColor(btn, ColorConstants::BLOCK_SLIDE_BLOCK_HOVER_COLOR);
		}

		else if (event->type() == QEvent::Leave) {
			Utilities::changeColor(btn, ColorConstants::BLOCK_SLIDE_BLOCK_COLOR);
		}
	}

	return QObject::eventFilter(watched, event);
}

void BlockSlideEngine::rotateLayoutRandomly() {
}

void BlockSlideEngine::rotate90Degrees() {
}

void BlockSlideEngine::transposeLayout() {
}

void BlockSlideEngine::tileBtnClick() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	std::array<int, 2> coords = buttonCoords.at(button);
	BlockSlideTile* tile = &tiles[coords[0]][coords[1]];
	if (tile->highlighted&&!tile->barrier) {
		moveCurrentBlock(coords);
	}
}

void BlockSlideEngine::slidingBlockBtnRightClick() {
	resetOnlyThePuzzle = true;
	resetGame();
	resetOnlyThePuzzle = false;
}

void BlockSlideEngine::slidingBlockBtnClick() {
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	for (SlidingBlock* block : slidingBlocks) {
		if (block->button == button) {
			currentSelectedBlock = block;
			break;
		}
	}
	clearHighlights();
	highlightPossibleMoves(currentSelectedBlock);
}

void BlockSlideEngine::animationFinished() {
	animationActive = false;
	enableButtons();
	checkIfWin();
}
