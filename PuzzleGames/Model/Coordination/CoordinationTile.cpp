#include "CoordinationTile.h"
#include"ColorConstants.h"
#include"ColorUtils.h"
#include<qdebug.h>

CoordinationTile::CoordinationTile(QPushButton* button)
	: button{ button }, tileType{ COORD_TILE_TYPE::DEFAULT }, hasBlock{ false } {};

CoordinationTile::CoordinationTile() {
}

void CoordinationTile::changeAppearance() {
	button->setText("");
	switch (tileType) {
	case COORD_TILE_TYPE::DEFAULT:
		ColorUtils::changeColor(button, ColorConstants::COORDINATION_DEFAULT_COLOR);
		break;
	case COORD_TILE_TYPE::BARRIER:
		ColorUtils::changeColor(button, ColorConstants::COORDINATION_BARRIER_COLOR);
		break;
	case COORD_TILE_TYPE::GOAL:
		ColorUtils::changeColor(button, ColorConstants::COORDINATION_DEFAULT_COLOR);
		button->setText("X");
		break;
	default:
		break;
	}
	//having a block should override anything
	if (hasBlock) {
		ColorUtils::changeColor(button, ColorConstants::COORDINATION_BLOCK_COLOR);
	}
}

void CoordinationTile::reset() {
	hasBlock = false;
}
