#include "PuzzleGames.h"
#include"ColorConstants.h"
#include<qregularexpression.h>
#include"ColorUtils.h"
#include"MinesweeperEngine.h"
#include"BattleshipEngine.h"
#include"FillSquaresEngine.h"
#include"BlockSlideEngine.h"
#include"BlockFillEngine.h"
#include"CoordinationEngine.h"
#include"TutorialDialog.h"
#include"qt_windows.h"
#include<stdexcept>

PuzzleGames::PuzzleGames(QWidget *parent)
    : QMainWindow(parent)
{
    srand(time(0));
    currentGame = NULL;
    ui.setupUi(this);
    ui.PuzzleMainGrid->setAlignment(Qt::AlignCenter);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    playButtons = { ui.MSweeperPlayBtn, ui.BShipPlayBtn,ui.FillSquaresPlayBtn,ui.BlockSlidePlayBtn,
                    ui.BlockFillPlayBtn,ui.CoordPlayBtn };

    playPuzzleSelectButtons = { ui.BlockSlidePlayBtn,ui.BlockFillPlayBtn,ui.CoordPlayBtn };

    darkButtons = { ui.PuzzleSelectForward,ui.PuzzleSelectBack, ui.ResetButton,ui.GoBackButton, ui.TutorialButton,
                     };
    darkButtons.insert(darkButtons.end(), playButtons.begin(), playButtons.end());     

    for (QPushButton* button : darkButtons) {
        setupDarkButtonPressRelease(button);
        button->installEventFilter(this);
    }

    for (QPushButton* button : playButtons) {
        connect(button, &QPushButton::clicked, this, &PuzzleGames::playButtonClick);
    }
    
    connect(ui.PuzzleSelectForward, &QPushButton::clicked, this, &PuzzleGames::puzzleSelectForwardClick);
    connect(ui.PuzzleSelectBack, &QPushButton::clicked, this, &PuzzleGames::puzzleSelectBackClick);
    connect(ui.ResetButton, &QPushButton::clicked, this, &PuzzleGames::resetBtnClick);
    connect(ui.GoBackButton, &QPushButton::clicked, this, &PuzzleGames::goBackBtnClick);
    connect(ui.TutorialButton, &QPushButton::clicked, this, &PuzzleGames::tutorialBtnClick);
}

GameEngine* PuzzleGames::createEngine() {
    switch (currentGameId) {
    case 0:
        return new MinesweeperEngine(this);
        break;
    case 1:
        return new BattleshipEngine(this);
        break;
    case 2:
        return new FillSquaresEngine(this);
        break;
    case 3:
        return new BlockSlideEngine(this);
        break;
    case 4:
        return new BlockFillEngine(this);
        break;
    case 5:
        return new CoordinationEngine(this);
        break;
    default:
        break;
    }
}

void PuzzleGames::setupDarkButtonPressRelease(QPushButton* button) {
    connect(button, &QPushButton::released, this, &PuzzleGames::darkButtonRelease);
    connect(button, &QPushButton::pressed, this, &PuzzleGames::darkButtonPress);
}
void PuzzleGames::changePuzzleGridSpacing(int newSpacing) {
    ui.PuzzleMainGrid->setSpacing(newSpacing);
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

void PuzzleGames::setupSlidingBlock(SlidingBlock& block, int row, int col) {
    QDifferentClicksButton* newButton = new QDifferentClicksButton(ui.PuzzleTileFrame);
    block.button = newButton;
}

QDifferentClicksButton* PuzzleGames::createButton(int row, int col, bool puzzleSelectGame) {
    if (row >= 0 && col >= 0) {
        QDifferentClicksButton* newButton;
        if (puzzleSelectGame) {
            newButton = new QDifferentClicksButton(ui.PuzzleTileFrame);
            ui.PuzzleMainGrid->addWidget(newButton, row, col);
        }
        else {
            newButton = new QDifferentClicksButton(ui.StandardGameTileFrame);
            ui.StandardGameMainGrid->addWidget(newButton, row, col);
        }

        return newButton;
    }
    else {
        throw std::invalid_argument("Row or column was negative. Cannot create button in grid with negative indices.");
    }
}


bool PuzzleGames::eventFilter(QObject* watched, QEvent* event) {
    QPushButton* btn = static_cast<QPushButton*>(watched);
    
    if (btn && btn->isEnabled()) {
        
        bool darkButton{ std::find(darkButtons.begin(),darkButtons.end(),btn) != darkButtons.end() };

        if (event->type() == QEvent::Enter && darkButton) {
            ColorUtils::changeColor(btn, ColorConstants::DARK_BUTTON_LIT_COLOR);
        }

        else if (event->type() == QEvent::Leave && darkButton) {
            ColorUtils::changeColor(btn, ColorConstants::DARK_BUTTON_DEFAULT_COLOR);
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void PuzzleGames::darkButtonRelease() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button->isEnabled()) {
        ColorUtils::changeColor(button, ColorConstants::DARK_BUTTON_LIT_COLOR);
    }
}

void PuzzleGames::playButtonClick() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    currentGameId = 0;
    auto iterator = std::find(playButtons.begin(), playButtons.end(), button);
    if (iterator != playButtons.end()) {
       currentGameId = iterator - playButtons.begin();
    }
    ui.MainStackedWidget->setCurrentIndex(1);
    bool puzzleSelectGame{ std::find(playPuzzleSelectButtons.begin(),playPuzzleSelectButtons.end(), button) != playPuzzleSelectButtons.end() };
    ui.GameStackedWidget->setCurrentIndex((puzzleSelectGame) ? 1 : 0);
    if (puzzleSelectGame) {
        ui.PuzzleSelectLabel->setText("Puzzle 1");
    }
    currentGame = createEngine();
    connectAndStartGame();
}

void PuzzleGames::puzzleSelectForwardClick() {
    PuzzleSelectGameEngine* engine = dynamic_cast<PuzzleSelectGameEngine*>(currentGame);
    engine->increasePuzzleIndex();
    ui.PuzzleSelectLabel->setText("Puzzle " + QString::number(engine->getCurrentIndex()+1));
}

void PuzzleGames::puzzleSelectBackClick() {
    PuzzleSelectGameEngine* engine = dynamic_cast<PuzzleSelectGameEngine*>(currentGame);
    engine->decreasePuzzleIndex();
    ui.PuzzleSelectLabel->setText("Puzzle " + QString::number(engine->getCurrentIndex()+1));
}

void PuzzleGames::connectAndStartGame() {
    ui.StatusLabel->setText("");
    ui.TopRightLabel->setText("");
    ui.TopLeftLabel->setText("");
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

void PuzzleGames::tutorialBtnClick() {
    TutorialDialog dialog = TutorialDialog(currentGameId,this);
    dialog.exec();
}

void PuzzleGames::darkButtonPress() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    ColorUtils::changeColor(button, ColorConstants::DARK_BUTTON_PRESS_COLOR);
}