#pragma once
#include<array>
#include<vector>
#include<qstring.h>
class BlockFillShape {
public:
	friend class BlockFillEngine;
	BlockFillShape(QChar name, QChar shapeType);
	void move(std::array<int, 2> toMove);
	bool inValidSpot();
	void rotateRight();
private:
	std::vector<std::array<int, 2>> coords;
	std::array<int, 2> currentAnchorPoint;
	QChar shapeType;
	QChar name;
};

