#pragma once
#include<QPushButton>

enum  TILE_TYPE { HIDDEN, BOMB, SAFE, BOMBS_AROUND };

class MinesweeperTile {
private:
	friend class MinesweeperEngine;

	bool hidden;
	QPushButton* button;
	TILE_TYPE tileType;
	int bombsAround;
	bool flagged;
public:
	void changeFlag();
	void changeHidden();
	MinesweeperTile(bool hidden, QPushButton* button, TILE_TYPE tileType, int bombsAround);
	MinesweeperTile();
	void calculateAndSetBombs(std::array<std::array<MinesweeperTile, 16>, 16>& tiles, std::map<QPushButton*, std::array<int, 2>>& buttonCoords);
	void reveal();
};

