#pragma once
#include"qpushbutton.h"
class BlockSlideTile {
private:
	friend class BlockSlideEngine;
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

