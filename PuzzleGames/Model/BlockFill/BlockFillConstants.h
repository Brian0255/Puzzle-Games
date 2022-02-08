#pragma once
#include"GameLayout.h"
#include<vector>
#include<array>
#include<qchar.h>
class BlockFillConstants {
public:
	static const std::vector<GameLayout<16>> layouts;
	static const std::array<QChar, 7> pieceNames;
};