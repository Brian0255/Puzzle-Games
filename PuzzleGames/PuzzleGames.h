#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PuzzleGames.h"
#include"GameEngine.h"

class PuzzleGames : public QMainWindow
{
    Q_OBJECT

public:
    bool eventFilter(QObject* watched, QEvent* event);
    PuzzleGames(QWidget *parent = Q_NULLPTR);
public slots:
    void darkButtonPress();
    void darkButtonRelease();
    void minesweeperPlayBtnClick();
    void resetBtnClick();
    void goBackBtnClick();
    void updateTopLeftLabel(QString newLabel);
    void updateTopRightLabel(QString newLabel);
    void updateStatusLabel(QString newLabel);
private:
    Ui::PuzzleGamesClass ui;
    GameEngine* currentGame;
};
