#include "BlockSlideTile.h"
#include"Utilities.h"
#include"ColorConstants.h"

BlockSlideTile::BlockSlideTile(QPushButton* button)
	:button{ button }, highlighted{ false }, goal{ false } {};

BlockSlideTile::BlockSlideTile() {
}

void BlockSlideTile::highlight() {
	highlighted = true;
	Utilities::changeColor(button, ColorConstants::BLOCK_SLIDE_HIGHLIGHT_COLOR);
}

void BlockSlideTile::clearHighlight() {
	if (highlighted) {
		highlighted = false;
		Utilities::changeColor(button, ColorConstants::BLOCK_SLIDE_DEFAULT_COLOR);
	}
}

void BlockSlideTile::reset() {
	barrier = false;
	highlighted = false;
	Utilities::changeColor(button, ColorConstants::BLOCK_SLIDE_DEFAULT_COLOR);
}
