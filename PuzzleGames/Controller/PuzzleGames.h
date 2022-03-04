#pragma once

#include <QtWidgets/QMainWindow>
#include "PuzzleGames.h"
#include"SlidingBlock.h"
#include"GameEngine.h"
#include"QDifferentClicksButton.h"
#include"ui_PuzzleGames.h"
#include<vector>
#include<map>
class PuzzleGames : public QMainWindow
{
    Q_OBJECT

public:
    bool eventFilter(QObject* watched, QEvent* event);
    PuzzleGames(QWidget *parent = Q_NULLPTR);

    QDifferentClicksButton* createButton(int row, int col, bool puzzleSelectGame);
    void setupSlidingBlock(SlidingBlock& block, int row, int col);

    void changePuzzleGridSpacing(int newSpacing);

    GameEngine* createEngine();
public slots:
    void darkButtonPress();
    void darkButtonRelease();

    void playButtonClick();

    void puzzleSelectForwardClick();
    void puzzleSelectBackClick();

    void connectAndStartGame();

    void resetBtnClick();
    void goBackBtnClick();
    void tutorialBtnClick();

    void updateTopLeftLabel(QString newLabel);
    void updateTopRightLabel(QString newLabel);
    void updateStatusLabel(QString newLabel);
private:
    Ui::PuzzleGamesClass ui;
    GameEngine* currentGame;
    std::vector<QPushButton*> darkButtons;
    std::vector<QPushButton*> playButtons;
    std::vector<QPushButton*> playPuzzleSelectButtons;
    int currentGameId;

    void setupDarkButtonPressRelease(QPushButton* button);
};
