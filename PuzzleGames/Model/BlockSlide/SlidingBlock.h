#pragma once
#include"QDifferentClicksButton.h"
#include<array>
struct SlidingBlock {
	QDifferentClicksButton* button;
	std::array<int, 2> coords;
};

