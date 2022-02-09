#pragma once
#include"qpushbutton.h"

enum class COORD_TILE_TYPE { BARRIER, GOAL, DEFAULT };

class CoordinationTile {
	friend class TileUtils;
private:
	friend class CoordinationEngine;
	bool hasBlock;
	COORD_TILE_TYPE tileType;
	QPushButton* button;
public:
	CoordinationTile(QPushButton* button);
	CoordinationTile();
	void changeAppearance();
	void reset();
};

