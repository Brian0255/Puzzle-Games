#include "GameEngine.h"
#include"ColorUtils.h"
#include<qpushbutton.h>
#include<qevent.h>
#include"ColorConstants.h"

bool GameEngine::eventFilter(QObject* watched, QEvent* event) {
    QPushButton* btn = static_cast<QPushButton*>(watched);
    if (btn && btn->isEnabled()) {
        if (event->type() == QEvent::Enter) {
            ColorUtils::changeColor(btn, ColorConstants::TILE_HOVER_COLOR);
        }

        else if (event->type() == QEvent::Leave) {
            ColorUtils::changeColor(btn, ColorConstants::TILE_DEFAULT_COLOR);
        }
    }

    return QObject::eventFilter(watched, event);
}



