#pragma once
#include<qobject.h>
#include"GameEngine.h"
#include"qpushbutton.h"
#include"MinesweeperTile.h"
#include"ui_PuzzleGames.h"
#include<array>

class MinesweeperEngine : public GameEngine {
    Q_OBJECT

public:
    MinesweeperEngine(Ui::PuzzleGamesClass* ui);
    ~MinesweeperEngine();
    void startEngine();
    void startGame(QPushButton*, int);
    void resetGame();
    void gameOver(QPushButton*);

    bool eventFilter(QObject* watched, QEvent* event);

    void revealTile(QPushButton* button);

    void checkIfWin();
    void disableButtons();
    int calcFlagsAroundTile(QPushButton* button);
    void setupTileBombCounts();
public slots:
    void tileButtonPress();
    void tileButtonClick();
    void tileRightClick();
    void tileMiddleClick();
    void resetButtonClick();
    
private:
    Ui::PuzzleGamesClass* ui;
    int bombs;
    int bombStartAmount{ 30 };
    std::array<std::array<MinesweeperTile, 16>, 16> tiles;
    bool gameActive{ false };
    std::map<QPushButton*, std::array<int, 2>> buttonCoords;
    std::map<std::array<int, 2>, bool> bombCoordsUsed;
};