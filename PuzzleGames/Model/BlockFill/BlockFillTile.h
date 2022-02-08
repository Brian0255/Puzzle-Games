#pragma once
#include"BlockFillShape.h"
#include"qpushbutton.h"

class BlockFillTile {
	friend class TileUtils;
	friend class BlockFillEngine;
public:

	BlockFillTile(QPushButton* button);
	BlockFillTile();
	void reset();
private:
	BlockFillShape* shape;
	bool barrier;
	QPushButton* button;
	bool goal;
};

