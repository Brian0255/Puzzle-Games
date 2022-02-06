#pragma once
#include"BlockFillLayout.h"
#include<vector>
#include<array>
#include<qchar.h>
class BlockFillConstants {
public:
	static const std::vector<BlockFillLayout> layouts;
	static const std::array<QChar, 7> pieceNames;
};