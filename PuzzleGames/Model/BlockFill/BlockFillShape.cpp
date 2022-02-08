#include"BlockFillShape.h"
#include"Utilities.h"
#include<qdebug.h>
BlockFillShape::BlockFillShape(QChar name, QChar shapeType)
	: name{ name }, shapeType{ shapeType }, currentAnchorPoint{ {} } {}

void BlockFillShape::move(std::array<int, 2> toMove) {
	for (auto& coord : coords) {
		coord[0] += toMove[0];
		coord[1] += toMove[1];
	}
	currentAnchorPoint[0] += toMove[0];
	currentAnchorPoint[1] += toMove[1];
}
;

bool BlockFillShape::inValidSpot() {
	for (auto& coord : coords) {
		int row = coord[0];
		int col = coord[1];
		bool invalidRow{ row < 0 || row > 15 };
		bool invalidCol{ col < 0 || col > 15 };
		if (invalidRow || invalidCol) {
			return false;
		}
	}
	return true;
}

void BlockFillShape::rotateRight() {
	//right rotation: find difference from anchor
	//diff = (x,y), change to (-y,x)
	//add to anchor coord, new coord for piece

	for (std::array<int, 2>&coord : coords) {
		std::array<int, 2> difference = Utilities::subtractIntArrays(currentAnchorPoint, coord);
		int temp = difference[0];
		difference[0] = difference[1] * -1;
		difference[1] = temp;
		coord = Utilities::addIntArrays(difference, currentAnchorPoint);
	}
}

