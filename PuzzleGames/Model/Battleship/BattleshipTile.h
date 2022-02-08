#pragma once
#include<QPushButton>

class BattleshipTile {
	friend class BattleshipEngine;
	friend class TileUtils;
private:
	char letter;
	bool hidden;
	bool isShip;
	bool crossedOff;
	QPushButton* button;
	int shipsIntersecting;
	bool secret;
public:
	void reveal();
	BattleshipTile(QPushButton* button);
	BattleshipTile();
	void calculateShipsIntersecting(std::array<std::array<BattleshipTile, 10>, 10>& battleshipTiles, std::map<QPushButton*, std::array<int, 2>>& buttonCoords);
	int calculateShipsNorth(std::map<QPushButton*, std::array<int, 2>>& buttonCoords, std::array<std::array<BattleshipTile, 10>, 10>& battleshipTiles);
	int calculateShipsSouth(std::map<QPushButton*, std::array<int, 2>>& buttonCoords, std::array<std::array<BattleshipTile, 10>, 10>& battleshipTiles);
	int calculateShipsEast(std::map<QPushButton*, std::array<int, 2>>& buttonCoords, std::array<std::array<BattleshipTile, 10>, 10>& battleshipTiles);
	int calculateShipsWest(std::map<QPushButton*, std::array<int, 2>>& buttonCoords, std::array<std::array<BattleshipTile, 10>, 10>& battleshipTiles);
};