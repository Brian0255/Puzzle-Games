#include "MinesweeperEngine.h"
#include"QDifferentClicksButton.h"
#include"ColorConstants.h"
#include"Utilities.h"

MinesweeperEngine::MinesweeperEngine(PuzzleGames* controller) : controller{ controller } {};

MinesweeperEngine::~MinesweeperEngine() {
    for (auto& tileArray : tiles) {
        for (MinesweeperTile tile : tileArray) {
            QPushButton* button = tile.button;
            delete button;
        }
    }
}

void MinesweeperEngine::startEngine() {
    srand(time(0));
    bombs = bombStartAmount;
    emit sendTopLeftLabelUpdate("");
    emit sendTopRightLabelUpdate("Bombs: " + QString::number(bombs));
    setupTiles();
}

void MinesweeperEngine::setupTiles() {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            QDifferentClicksButton* tileBtn = controller->createMinesweeperButton(i, j);
            tileBtn->setStyleSheet(
                "border: 0px;"
                "background-color: rgb(200,200,200);"
                "border-radius: 2px;"
                "font: 14pt \"Segoe UI Semilight\";"
                "color: rgb(255, 255, 255); "
            );
            tileBtn->setFixedSize(32, 32);
            tileBtn->installEventFilter(this);
            MinesweeperTile tile = MinesweeperTile(true, tileBtn, TILE_TYPE::HIDDEN, 0);
            connect(tileBtn, &QDifferentClicksButton::leftClicked, this, &MinesweeperEngine::tileButtonClick);
            connect(tileBtn, &QDifferentClicksButton::rightClicked, this, &MinesweeperEngine::tileRightClick);
            connect(tileBtn, &QDifferentClicksButton::middleClicked, this, &MinesweeperEngine::tileMiddleClick);
            std::array<int, 2> coords = { i,j };
            tiles[i][j] = tile;
            bombCoordsUsed.insert({ { i,j }, false });
            buttonCoords.insert({ tileBtn, coords });
        }
    }
}

void MinesweeperEngine::startGame(QPushButton* firstBtnClicked, int numBombs) {
    int max = tiles.size();
    std::array<int, 2> coords = buttonCoords.at(firstBtnClicked);
    for (int i = 0; i < numBombs; ++i) {
        bool valid{ false };
        while (!valid) {
            int row = rand() % max;
            int col = rand() % max;
            if ((row != coords[0] || col != coords[1]) &&
                (tiles[row][col].tileType != TILE_TYPE::BOMB)) {
                valid = true;
                tiles[row][col].tileType = TILE_TYPE::BOMB;
            }
        }
    }
    emit sendTopRightLabelUpdate("Bombs: " + QString::number(bombs));
}

void MinesweeperEngine::tileRightClick() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    std::array<int, 2> coords = buttonCoords.at(button);
    MinesweeperTile tile = tiles[coords[0]][coords[1]];
    if (tile.tileType != TILE_TYPE::SAFE && tile.tileType != TILE_TYPE::BOMBS_AROUND) {
        button->setText((button->text() == "X") ? "" : "X");
        bombs += (button->text() == "X") ? -1 : 1;
        tiles[coords[0]][coords[1]].changeFlag();
        emit sendTopRightLabelUpdate("Bombs: " + QString::number(bombs));
    }
}

void MinesweeperEngine::tileMiddleClick() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    std::array<int, 2> coords = buttonCoords.at(button);
    int row = coords[0];
    int col = coords[1];
    if (tiles[row][col].tileType == TILE_TYPE::BOMBS_AROUND) {
        if (calcFlagsAroundTile(button) == button->text().toInt()) {
            for (int rowOffset = -1; rowOffset < 2; ++rowOffset) {
                for (int colOffset = -1; colOffset < 2; ++colOffset) {
                    if ((rowOffset != 0) || (colOffset != 0)) {
                        int checkRow = row + rowOffset;
                        int checkCol = col + colOffset;
                        if (checkRow >= 0 && checkRow < tiles.size()) {
                            if (checkCol >= 0 && checkCol < tiles.size()) {
                                MinesweeperTile tile = tiles[checkRow][checkCol];
                                if (tile.hidden && (!tile.flagged)) {
                                    revealTile(tiles[checkRow][checkCol].button);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    checkIfWin();
}

void MinesweeperEngine::revealTile(QPushButton* button) {
    std::array<int, 2> coords = buttonCoords.at(button);
    int row = coords[0];
    int col = coords[1];
    MinesweeperTile* mainTile = &tiles[row][col];
    if (mainTile->tileType == TILE_TYPE::BOMB) {
        gameOver(button);
    }
    else {
        mainTile->reveal();
        Utilities::Utilities::changeColor(button, ColorConstants::TILE_UNCOVERED_COLOR);
        button->removeEventFilter(this);
        if (mainTile->tileType == TILE_TYPE::SAFE) {
            for (int rowOffset = -1; rowOffset < 2; ++rowOffset) {
                for (int colOffset = -1; colOffset < 2; ++colOffset) {
                    if ((rowOffset != 0) || (colOffset != 0)) {
                        int checkRow = row + rowOffset;
                        int checkCol = col + colOffset;
                        if (checkRow >= 0 && checkRow < tiles.size()) {
                            if (checkCol >= 0 && checkCol < tiles.size()) {
                                MinesweeperTile tile = tiles[checkRow][checkCol];
                                if (tile.hidden) {
                                    revealTile(tile.button);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void MinesweeperEngine::resetGame() {
    for (int i = 0; i < tiles.size(); ++i) {
        for (int j = 0; j < tiles.size(); ++j) {
            MinesweeperTile* tile = &tiles[i][j];
            tile->tileType = (TILE_TYPE::HIDDEN);
            Utilities::Utilities::changeColor(tile->button, ColorConstants::TILE_DEFAULT_COLOR);
            tile->button->installEventFilter(this);
            tile->button->setEnabled(true);
            tile->button->setText("");
            if (!tile->hidden) {
                tile->changeHidden();
            }
            if (tile->flagged) {
                tile->changeFlag();
            }
            gameActive = false;
        }
    }
    emit sendStatusLabelUpdate("");
    bombs = bombStartAmount;
    emit sendTopRightLabelUpdate("Bombs: " + QString::number(bombs));
}

void MinesweeperEngine::gameOver(QPushButton* hit) {
    hit->setText("X");
    Utilities::Utilities::changeColor(hit, ColorConstants::MINESWEEPER_HIT_BOMB_COLOR);
    disableButtons();
    for (std::array<MinesweeperTile, 16> tileRow : tiles) {
        for (MinesweeperTile tile : tileRow) {
            if (tile.tileType == TILE_TYPE::BOMB && tile.button != hit) {
                Utilities::Utilities::changeColor(tile.button, ColorConstants::TILE_UNCOVERED_COLOR);
                tile.button->setText("X");
            }
        }
    }
    emit sendStatusLabelUpdate("Game over!");
}

void MinesweeperEngine::disableButtons() {
    for (std::array<MinesweeperTile, 16> tileRow : tiles) {
        for (MinesweeperTile tile : tileRow) {
            tile.button->setEnabled(false);
        }
    }
}

void MinesweeperEngine::checkIfWin() {
    bool win{ true };
    for (std::array<MinesweeperTile, 16> tileRow : tiles) {
        for (MinesweeperTile tile : tileRow) {
            if (tile.tileType == TILE_TYPE::HIDDEN) {
                win = false;
            }
        }
    }
    if (win) {
        disableButtons();
        emit sendStatusLabelUpdate("You win!");
    }
}

void MinesweeperEngine::resetButtonClick() {
    resetGame();
}

void MinesweeperEngine::tileButtonPress() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button->isEnabled())
        Utilities::changeColor(button, ColorConstants::TILE_PRESS_COLOR);
}

void MinesweeperEngine::tileButtonClick() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button->isEnabled()) {
        Utilities::changeColor(button, ColorConstants::TILE_UNCOVERED_COLOR);

        if (!gameActive) {
            gameActive = true;
            startGame(button, bombStartAmount);
            setupTileBombCounts();
        }
        std::array<int, 2> coords = buttonCoords.at(button);
        MinesweeperTile tile = tiles[coords[0]][coords[1]];
        if (tile.tileType == TILE_TYPE::BOMB) {
            gameOver(button);
        }
        else {
            revealTile(button);
            checkIfWin();
        }
    }
}

int MinesweeperEngine::calcFlagsAroundTile(QPushButton* button) {
    std::array<int, 2> coords = buttonCoords.at(button);
    int row = coords[0];
    int col = coords[1];
    MinesweeperTile mainTile = tiles[row][col];
    int total = 0;
    for (int rowOffset = -1; rowOffset < 2; ++rowOffset) {
        for (int colOffset = -1; colOffset < 2; ++colOffset) {
            if ((rowOffset != 0) || (colOffset != 0)) {
                int checkRow = row + rowOffset;
                int checkCol = col + colOffset;
                if (checkRow >= 0 && checkRow < tiles.size()) {
                    if (checkCol >= 0 && checkCol < tiles.size()) {
                        MinesweeperTile tile = tiles[checkRow][checkCol];
                        if (tile.flagged) {
                            ++total;
                        }
                    }
                }
            }
        }
    }
    return total;
}

void MinesweeperEngine::setupTileBombCounts() {
    for (auto& array : tiles) {
        for (MinesweeperTile& tile : array) {
            tile.calculateAndSetBombs(tiles, buttonCoords);
        }
    }
}