#include "PuzzleGames.h"
#include"ColorConstants.h"
#include<qregularexpression.h>
#include"Utilities.h"
#include"MinesweeperEngine.h"
#include"BattleshipEngine.h"
#include"qt_windows.h"

PuzzleGames::PuzzleGames(QWidget *parent)
    : QMainWindow(parent)
{
    currentGame = NULL;
    ui.setupUi(this);
    ui.MSweeperPlayBtn->installEventFilter(this);
    ui.BShipPlayBtn->installEventFilter(this);
    ui.GoBackButton->installEventFilter(this);
    ui.ResetButton->installEventFilter(this);
    connect(ui.MSweeperPlayBtn, &QPushButton::released, this, &PuzzleGames::darkButtonRelease);
    connect(ui.MSweeperPlayBtn, &QPushButton::pressed, this, &PuzzleGames::darkButtonPress);
    connect(ui.MSweeperPlayBtn, &QPushButton::clicked, this, &PuzzleGames::minesweeperPlayBtnClick);

    connect(ui.BShipPlayBtn, &QPushButton::released, this, &PuzzleGames::darkButtonRelease);
    connect(ui.BShipPlayBtn, &QPushButton::pressed, this, &PuzzleGames::darkButtonPress);
    connect(ui.BShipPlayBtn, &QPushButton::clicked, this, &PuzzleGames::battleshipPlayBtnClick);

    connect(ui.ResetButton, &QPushButton::released, this, &PuzzleGames::darkButtonRelease);
    connect(ui.ResetButton, &QPushButton::pressed, this, &PuzzleGames::darkButtonPress);
    connect(ui.ResetButton, &QPushButton::clicked, this, &PuzzleGames::resetBtnClick);

    connect(ui.GoBackButton, &QPushButton::released, this, &PuzzleGames::darkButtonRelease);
    connect(ui.GoBackButton, &QPushButton::pressed, this, &PuzzleGames::darkButtonPress);
    connect(ui.GoBackButton, &QPushButton::clicked, this, &PuzzleGames::goBackBtnClick);
}

void PuzzleGames::updateTopLeftLabel(QString newLabel) {
    ui.TopLeftLabel->setText(newLabel);
}

void PuzzleGames::updateTopRightLabel(QString newLabel) {
    ui.TopRightLabel->setText(newLabel);
}

void PuzzleGames::updateStatusLabel(QString newLabel) {
    ui.StatusLabel->setText(newLabel);
}

QDifferentClicksButton* PuzzleGames::createMinesweeperButton(int row, int col) {
    QDifferentClicksButton* newButton = new QDifferentClicksButton(ui.MSweeperTileFrame);
    ui.MSweeperMainGrid->addWidget(newButton, row, col);
    return newButton;
}

QDifferentClicksButton* PuzzleGames::createBattleshipButton(int row, int col) {
    QDifferentClicksButton* newButton = new QDifferentClicksButton(ui.BShipTileFrame);
    ui.BShipMainGrid->addWidget(newButton, row, col);
    return newButton;
}

bool PuzzleGames::eventFilter(QObject* watched, QEvent* event) {
    QPushButton* btn = static_cast<QPushButton*>(watched);
    
    if (btn && btn->isEnabled()) {
        
        bool darkButton{ (Utilities::getColor(btn) == ColorConstants::DARK_BUTTON_DEFAULT_COLOR) ||
                         (Utilities::getColor(btn) == ColorConstants::DARK_BUTTON_LIT_COLOR)     ||
                         (Utilities::getColor(btn) == ColorConstants::DARK_BUTTON_PRESS_COLOR) };

        if (event->type() == QEvent::Enter && darkButton) {
            Utilities::changeColor(btn, ColorConstants::DARK_BUTTON_LIT_COLOR);
        }

        else if (event->type() == QEvent::Leave && darkButton) {
            Utilities::changeColor(btn, ColorConstants::DARK_BUTTON_DEFAULT_COLOR);
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void PuzzleGames::darkButtonRelease() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button->isEnabled()) {
        Utilities::changeColor(button, ColorConstants::DARK_BUTTON_LIT_COLOR);
    }
}

void PuzzleGames::minesweeperPlayBtnClick() {
    ui.MainStackedWidget->setCurrentIndex(1);
    ui.GameStackedWidget->setCurrentIndex(0);
    currentGame = new MinesweeperEngine(this);
    connectAndStartGame();
}

void PuzzleGames::connectAndStartGame() {
    connect(currentGame, &GameEngine::sendStatusLabelUpdate, this, &PuzzleGames::updateStatusLabel);
    connect(currentGame, &GameEngine::sendTopLeftLabelUpdate, this, &PuzzleGames::updateTopLeftLabel);
    connect(currentGame, &GameEngine::sendTopRightLabelUpdate, this, &PuzzleGames::updateTopRightLabel);
    currentGame->startEngine();
}

void PuzzleGames::battleshipPlayBtnClick() {
    ui.MainStackedWidget->setCurrentIndex(1);
    ui.GameStackedWidget->setCurrentIndex(1);
    currentGame = new BattleshipEngine(this);
    connectAndStartGame();
}

void PuzzleGames::resetBtnClick() {
    currentGame->resetGame();
}

void PuzzleGames::goBackBtnClick() {
    delete currentGame;
    ui.MainStackedWidget->setCurrentIndex(0);
}

void PuzzleGames::darkButtonPress() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    Utilities::changeColor(button, ColorConstants::DARK_BUTTON_PRESS_COLOR);
}