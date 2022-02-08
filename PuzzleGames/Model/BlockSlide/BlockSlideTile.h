#pragma once
#include"qpushbutton.h"
class BlockSlideTile {
	friend class TileUtils;
	friend class BlockSlideEngine;
private:
	bool highlighted;
	bool barrier;
	bool goal;
	QPushButton* button;
public:
	BlockSlideTile(QPushButton* button);
	BlockSlideTile();
	void highlight();
	void clearHighlight();
	void reset();
};

