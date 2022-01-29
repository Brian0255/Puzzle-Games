#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PuzzleGames.h"
#include"GameEngine.h"
#include"QDifferentClicksButton.h"

class PuzzleGames : public QMainWindow
{
    Q_OBJECT

public:
    bool eventFilter(QObject* watched, QEvent* event);
    PuzzleGames(QWidget *parent = Q_NULLPTR);
    QDifferentClicksButton* createMinesweeperButton(int row, int col);
    QDifferentClicksButton* createBattleshipButton(int row, int col);
public slots:
    void darkButtonPress();
    void darkButtonRelease();
    void minesweeperPlayBtnClick();
    void connectAndStartGame();
    void battleshipPlayBtnClick();
    void resetBtnClick();
    void goBackBtnClick();
    void updateTopLeftLabel(QString newLabel);
    void updateTopRightLabel(QString newLabel);
    void updateStatusLabel(QString newLabel);
private:
    Ui::PuzzleGamesClass ui;
    GameEngine* currentGame;
};
