#include "PuzzleGames.h"
#include"ColorConstants.h"
#include<qregularexpression.h>
#include"Utilities.h"
#include"MinesweeperEngine.h"
#include"BattleshipEngine.h"
#include"FillSquaresEngine.h"
#include"BlockSlideEngine.h"
#include"BlockFillEngine.h"
#include"qt_windows.h"

PuzzleGames::PuzzleGames(QWidget *parent)
    : QMainWindow(parent)
{
    currentGame = NULL;
    ui.setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    darkButtons = { ui.MSweeperPlayBtn, ui.BShipPlayBtn,ui.GoBackButton,ui.ResetButton, ui.FillSquaresPlayBtn,
                    ui.BlockSlidePlayBtn, ui.BlockSlideBack, ui.BlockSlideForward,ui.BlockFillPlayBtn,
                    ui.BlockFillForward,ui.BlockFillBack};
    for (QPushButton* button : darkButtons) {
        setupDarkButtonPressRelease(button);
        button->installEventFilter(this);
    }
    connect(ui.MSweeperPlayBtn, &QPushButton::clicked, this, &PuzzleGames::minesweeperPlayBtnClick);
    connect(ui.BShipPlayBtn, &QPushButton::clicked, this, &PuzzleGames::battleshipPlayBtnClick);
    connect(ui.FillSquaresPlayBtn, &QPushButton::clicked, this, &PuzzleGames::fillSquaresPlayBtnClick);
    connect(ui.ResetButton, &QPushButton::clicked, this, &PuzzleGames::resetBtnClick);
    connect(ui.GoBackButton, &QPushButton::clicked, this, &PuzzleGames::goBackBtnClick);

    connect(ui.BlockSlidePlayBtn, &QPushButton::clicked, this, &PuzzleGames::blockSlidePlayBtnClick);
    connect(ui.BlockSlideForward, &QPushButton::clicked, this, &PuzzleGames::blockSlideForwardClick);
    connect(ui.BlockSlideBack, &QPushButton::clicked, this, &PuzzleGames::blockSlideBackClick);

    connect(ui.BlockFillPlayBtn, &QPushButton::clicked, this, &PuzzleGames::blockFillPlayBtnClick);
    connect(ui.BlockFillForward, &QPushButton::clicked, this, &PuzzleGames::blockFillForwardClick);
    connect(ui.BlockFillBack, &QPushButton::clicked, this, &PuzzleGames::blockFillBackClick);
}

void PuzzleGames::setupDarkButtonPressRelease(QPushButton* button) {
    connect(button, &QPushButton::released, this, &PuzzleGames::darkButtonRelease);
    connect(button, &QPushButton::pressed, this, &PuzzleGames::darkButtonPress);
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

QDifferentClicksButton* PuzzleGames::createFillSquaresButton(int row, int col) {
    QDifferentClicksButton* newButton = new QDifferentClicksButton(ui.FillSquaresTileFrame);
    ui.FillSquaresMainGrid->addWidget(newButton, row, col);
    return newButton;
}

QDifferentClicksButton* PuzzleGames::createBlockSlideButton(int row, int col) {
    QDifferentClicksButton* newButton = new QDifferentClicksButton(ui.BlockSlideTileFrame);
    ui.BlockSlideMainGrid->addWidget(newButton, row, col);
    return newButton;
}

QDifferentClicksButton* PuzzleGames::createBlockFillButton(int row, int col) {
    QDifferentClicksButton* newButton = new QDifferentClicksButton(ui.BlockFillTileFrame);
    ui.BlockFillMainGrid->addWidget(newButton, row, col);
    return newButton;
}

void PuzzleGames::setupSlidingBlock(SlidingBlock& block,int row, int col) {
    QDifferentClicksButton* newButton = new QDifferentClicksButton(ui.BlockSlideTileFrame);
    block.button = newButton;
}

bool PuzzleGames::eventFilter(QObject* watched, QEvent* event) {
    QPushButton* btn = static_cast<QPushButton*>(watched);
    
    if (btn && btn->isEnabled()) {
        
        bool darkButton{ std::find(darkButtons.begin(),darkButtons.end(),btn) != darkButtons.end() };

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

void PuzzleGames::battleshipPlayBtnClick() {
    ui.MainStackedWidget->setCurrentIndex(1);
    ui.GameStackedWidget->setCurrentIndex(1);
    currentGame = new BattleshipEngine(this);
    connectAndStartGame();
}

void PuzzleGames::fillSquaresPlayBtnClick() {
    ui.MainStackedWidget->setCurrentIndex(1);
    ui.GameStackedWidget->setCurrentIndex(2);
    currentGame = new FillSquaresEngine(this);
    connectAndStartGame();
}

void PuzzleGames::blockSlidePlayBtnClick() {
    ui.MainStackedWidget->setCurrentIndex(1);
    ui.GameStackedWidget->setCurrentIndex(3);
    ui.BlockSlidePuzzleLabel->setText("Puzzle 1");
    currentGame = new BlockSlideEngine(this);
    connectAndStartGame();
}

void PuzzleGames::blockFillPlayBtnClick() {
    ui.MainStackedWidget->setCurrentIndex(1);
    ui.GameStackedWidget->setCurrentIndex(4);
    ui.BlockFillPuzzleLabel->setText("Puzzle 1");
    currentGame = new BlockFillEngine(this);
    ui.BlockFillTileFrame->installEventFilter(currentGame);
    connectAndStartGame();
}

void PuzzleGames::blockSlideForwardClick() {
    BlockSlideEngine* blockSlideGame = dynamic_cast<BlockSlideEngine*>(currentGame);
    blockSlideGame->increasePuzzleIndex();
    ui.BlockSlidePuzzleLabel->setText("Puzzle " + QString::number(blockSlideGame->getCurrentIndex() + 1));
    blockSlideGame->resetGame();
}

void PuzzleGames::blockSlideBackClick() {
    BlockSlideEngine* blockSlideGame = dynamic_cast<BlockSlideEngine*>(currentGame);
    blockSlideGame->decreasePuzzleIndex();
    ui.BlockSlidePuzzleLabel->setText("Puzzle " + QString::number(blockSlideGame->getCurrentIndex() + 1));
    blockSlideGame->resetGame();
}

void PuzzleGames::blockFillForwardClick() {
    BlockFillEngine* blockFillGame = dynamic_cast<BlockFillEngine*>(currentGame);
    blockFillGame->increasePuzzleIndex();
    ui.BlockFillPuzzleLabel->setText("Puzzle " + QString::number(blockFillGame->getCurrentIndex() + 1));
    blockFillGame->resetGame();
}

void PuzzleGames::blockFillBackClick() {
    BlockFillEngine* blockFillGame = dynamic_cast<BlockFillEngine*>(currentGame);
    blockFillGame->decreasePuzzleIndex();
    ui.BlockFillPuzzleLabel->setText("Puzzle " + QString::number(blockFillGame->getCurrentIndex() + 1));
    blockFillGame->resetGame();
}

void PuzzleGames::connectAndStartGame() {
    ui.StatusLabel->setText("");
    connect(currentGame, &GameEngine::sendStatusLabelUpdate, this, &PuzzleGames::updateStatusLabel);
    connect(currentGame, &GameEngine::sendTopLeftLabelUpdate, this, &PuzzleGames::updateTopLeftLabel);
    connect(currentGame, &GameEngine::sendTopRightLabelUpdate, this, &PuzzleGames::updateTopRightLabel);
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