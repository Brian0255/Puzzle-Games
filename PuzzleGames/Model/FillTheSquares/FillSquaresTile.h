#pragma once
#include<qpushbutton.h>
class FillSquaresTile {
private:
	friend class FillSquaresEngine;
	friend class TileUtils;
	bool XSpot;
	bool filled;
	QPushButton* button;
public:
	FillSquaresTile(QPushButton* button);
	FillSquaresTile();
	void fill();
	void reset();
};

