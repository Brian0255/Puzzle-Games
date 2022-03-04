#include "BlockSlideTile.h"
#include"ColorUtils.h"
#include"ColorConstants.h"

BlockSlideTile::BlockSlideTile(QPushButton* button)
	:button{ button }, highlighted{ false }, goal{ false }, barrier{ false } {};

BlockSlideTile::BlockSlideTile()
	:button{ NULL }, highlighted{ false }, goal{ false }, barrier{ false } {};

void BlockSlideTile::highlight() {
	highlighted = true;
	ColorUtils::changeColor(button, ColorConstants::BLOCK_SLIDE_HIGHLIGHT_COLOR);
}

void BlockSlideTile::clearHighlight() {
	if (highlighted) {
		highlighted = false;
		ColorUtils::changeColor(button, ColorConstants::BLOCK_SLIDE_DEFAULT_COLOR);
	}
}

void BlockSlideTile::reset() {
	barrier = false;
	highlighted = false;
	ColorUtils::changeColor(button, ColorConstants::BLOCK_SLIDE_DEFAULT_COLOR);
}
