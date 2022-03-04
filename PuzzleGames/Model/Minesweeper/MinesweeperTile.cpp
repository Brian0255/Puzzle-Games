#include "MinesweeperTile.h"

void MinesweeperTile::changeFlag() {
    flagged = !flagged;
}

void MinesweeperTile::changeHidden() {
    hidden = !hidden;
}

MinesweeperTile::MinesweeperTile(bool hidden, QPushButton* button, TILE_TYPE tileType, int bombsAround)
    :button{ button }, hidden{ hidden }, tileType{ tileType }, bombsAround{ bombsAround }, flagged{ false } {};

MinesweeperTile::MinesweeperTile() 
    :button{ NULL }, hidden{ true }, tileType{ TILE_TYPE::HIDDEN }, bombsAround{ -1 }, flagged{ false } {};

void MinesweeperTile::calculateAndSetBombs(std::array<std::array<MinesweeperTile, 16>, 16>& tiles, std::map<QPushButton*, std::array<int, 2>>& buttonCoords) {
    std::array<int, 2> coords = buttonCoords.at(button);
    int row = coords[0];
    int col = coords[1];
    int total = 0;
    for (int rowOffset = -1; rowOffset < 2; ++rowOffset) {
        for (int colOffset = -1; colOffset < 2; ++colOffset) {
            if ((rowOffset != 0) || (colOffset != 0)) { //avoid checking the square we're on
                int checkRow = row + rowOffset;
                int checkCol = col + colOffset;
                if (checkRow >= 0 && checkRow < tiles.size()) {
                    if (checkCol >= 0 && checkCol < tiles.size()) {
                        MinesweeperTile tile = tiles[checkRow][checkCol];
                        if (tile.tileType == TILE_TYPE::BOMB) {
                            ++total;
                        }
                    }
                }
            }
        }
    }
    bombsAround = total;
}

void MinesweeperTile::reveal() {
    button->setText((bombsAround > 0) ? QString::number(bombsAround) : "");
    tileType = (bombsAround == 0) ? TILE_TYPE::SAFE : TILE_TYPE::BOMBS_AROUND;
    changeHidden();
}
