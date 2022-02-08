#include "CoordinationTile.h"
#include"ColorConstants.h"
#include"ColorUtils.h"

CoordinationTile::CoordinationTile(QPushButton* button)
	: button{ button }, tileType{ DEFAULT }, hasBlock{ false } {};

CoordinationTile::CoordinationTile() {
}

void CoordinationTile::changeAppearance() {
	button->setText("");
	switch (tileType) {
	case DEFAULT :
		ColorUtils::changeColor(button, ColorConstants::COORDINATION_DEFAULT_COLOR);
		break;
	case BARRIER:
		ColorUtils::changeColor(button, ColorConstants::COORDINATION_BARRIER_COLOR);
		break;
	case GOAL:
		ColorUtils::changeColor(button, ColorConstants::COORDINATION_DEFAULT_COLOR);
		ColorUtils::changeTextColor(button, ColorConstants::COORDINATION_GOAL_COLOR);
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
