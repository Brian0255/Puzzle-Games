#include "BlockFillTile.h"
#include"Utilities.h"
#include"ColorConstants.h"

BlockFillTile::BlockFillTile(QPushButton* button)
	: button{ button }, shape{ NULL }, goal{ false }, barrier{ false } {}

BlockFillTile::BlockFillTile() {
}
void BlockFillTile::reset() {
	shape = NULL;
	barrier = false;
	goal = false;
	Utilities::changeColor(button, ColorConstants::BLOCK_FILL_DEFAULT_TILE_COLOR);
}
;
