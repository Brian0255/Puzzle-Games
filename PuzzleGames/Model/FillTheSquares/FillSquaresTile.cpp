#include "FillSquaresTile.h"
#include"ColorConstants.h"
#include"ColorUtils.h"

FillSquaresTile::FillSquaresTile(QPushButton* button) 
	:button(button),filled(false),XSpot(false){}

FillSquaresTile::FillSquaresTile() {
}

void FillSquaresTile::fill() {
	filled = true;
}

void FillSquaresTile::reset() {
	if (!XSpot) {
		ColorUtils::changeColor(button, ColorConstants::TILE_DEFAULT_COLOR);
		filled = false;
		button->setEnabled(true);
	}
}
