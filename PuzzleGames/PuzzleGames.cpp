#include "PuzzleGames.h"
#include"ColorConstants.h"
#include<qregularexpression.h>
#include"Utilities.h"
#include"MinesweeperEngine.h"
#include"qt_windows.h"

PuzzleGames::PuzzleGames(QWidget *parent)
    : QMainWindow(parent)
{
    currentGame = NULL;
    ui.setupUi(this);
    ui.MSweeperPlayBtn->installEventFilter(this);
    ui.GoBackButton->installEventFilter(this);
    ui.ResetButton->installEventFilter(this);
    connect(ui.MSweeperPlayBtn, &QPushButton::released, this, &PuzzleGames::darkButtonRelease);
    connect(ui.MSweeperPlayBtn, &QPushButton::pressed, this, &PuzzleGames::darkButtonPress);
    connect(ui.MSweeperPlayBtn, &QPushButton::clicked, this, &PuzzleGames::minesweeperPlayBtnClick);

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
    currentGame = new MinesweeperEngine(&ui);
    currentGame->startEngine();
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