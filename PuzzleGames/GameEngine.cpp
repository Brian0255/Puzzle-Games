#include "GameEngine.h"
#include"Utilities.h"
#include<qpushbutton.h>
#include<qevent.h>
#include"ColorConstants.h"

void GameEngine::startEngine() {
}

void GameEngine::resetGame() {
}

GameEngine::GameEngine() {
}

GameEngine::~GameEngine() {
}

bool GameEngine::eventFilter(QObject* watched, QEvent* event) {
    QPushButton* btn = static_cast<QPushButton*>(watched);
    if (btn && btn->isEnabled()) {
        if (event->type() == QEvent::Enter) {
            Utilities::changeColor(btn, ColorConstants::TILE_HOVER_COLOR);
        }

        else if (event->type() == QEvent::Leave) {
            Utilities::changeColor(btn, ColorConstants::TILE_DEFAULT_COLOR);
        }
    }

    return QObject::eventFilter(watched, event);
}


