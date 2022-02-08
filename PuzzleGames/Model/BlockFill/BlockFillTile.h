#pragma once
#include"BlockFillShape.h"
#include"qpushbutton.h"

class BlockFillTile {
public:
	friend class BlockFillEngine;

	BlockFillTile(QPushButton* button);
	BlockFillTile();
	void reset();
private:
	BlockFillShape* shape;
	bool barrier;
	QPushButton* button;
	bool goal;
};

