#include "BattleshipTile.h"
#include <qDebug>

BattleshipTile::BattleshipTile(QPushButton* button)
    :hidden{ true }, isShip{ false }, shipsIntersecting{ 0 }, button{ button }, crossedOff{ false } {}

BattleshipTile::BattleshipTile() {}

void BattleshipTile::calculateShipsIntersecting(std::array<std::array<BattleshipTile, 10>, 10>& battleshipTiles, std::map<QPushButton*, std::array<int, 2>>& buttonCoords) {
    shipsIntersecting = 0;
    shipsIntersecting += calculateShipsNorth(buttonCoords, battleshipTiles);
    shipsIntersecting += calculateShipsSouth(buttonCoords, battleshipTiles);
    shipsIntersecting += calculateShipsEast(buttonCoords, battleshipTiles);
    shipsIntersecting += calculateShipsWest(buttonCoords, battleshipTiles);
}

int BattleshipTile::calculateShipsNorth(std::map<QPushButton*, std::array<int, 2>>& buttonCoords, std::array<std::array<BattleshipTile, 10>, 10>& BattleshipTiles) {
    std::array<int, 2> coords = buttonCoords.at(button);
    int row = coords[0];
    int col = coords[1];
    int total{ 0 };
    for (int i{ row - 1 }; i >= 0; --i) {
        BattleshipTile BattleshipTile = BattleshipTiles[i][col];
        if (BattleshipTile.isShip) {
            ++total;
        }
    }
    return total;
}

int BattleshipTile::calculateShipsSouth(std::map<QPushButton*, std::array<int, 2>>& buttonCoords, std::array<std::array<BattleshipTile, 10>, 10>& BattleshipTiles) {
    std::array<int, 2> coords = buttonCoords.at(button);
    int row = coords[0];
    int col = coords[1];
    int total{ 0 };
    for (int i{ row + 1 }; i < BattleshipTiles.size(); ++i) {
        BattleshipTile BattleshipTile = BattleshipTiles[i][col];
        if (BattleshipTile.isShip) {
            ++total;
        }
    }
    return total;
}

int BattleshipTile::calculateShipsWest(std::map<QPushButton*, std::array<int, 2>>& buttonCoords, std::array<std::array<BattleshipTile, 10>, 10>& BattleshipTiles) {
    std::array<int, 2> coords = buttonCoords.at(button);
    int row = coords[0];
    int col = coords[1];
    int total{ 0 };
    for (int i{ col - 1 }; i >= 0; --i) {
        BattleshipTile BattleshipTile = BattleshipTiles[row][i];
        if (BattleshipTile.isShip) {
            ++total;
        }
    }
    return total;
}

int BattleshipTile::calculateShipsEast(std::map<QPushButton*, std::array<int, 2>>& buttonCoords, std::array<std::array<BattleshipTile, 10>, 10>& BattleshipTiles) {
    std::array<int, 2> coords = buttonCoords.at(button);
    int row = coords[0];
    int col = coords[1];
    int total{ 0 };
    for (int i{ col + 1 }; i < BattleshipTiles[0].size(); ++i) {
        BattleshipTile BattleshipTile = BattleshipTiles[row][i];
        if (BattleshipTile.isShip) {
            ++total;
        }
    }
    return total;
}

void BattleshipTile::reveal() {
    if (isShip) {
        button->setText(QString(letter));
    }
    else {
        button->setText((shipsIntersecting > 0) ? QString::number(shipsIntersecting) : "");
    }
    hidden = false;
}
