#include "TutorialDialog.h"
#include"TutorialConstants.h"
#include"ColorUtils.h"
#include"ColorConstants.h"

TutorialDialog::TutorialDialog(int index, QWidget *parent)
	: currentIndex{ index }, QDialog(parent)
{
	ui.setupUi(this);
	ui.ControlsStackedWidget->setCurrentIndex(currentIndex);
	ui.RulesStackedWidget->setCurrentIndex(currentIndex);
	ui.TutorialDesc->setText(TutorialConstants::TUTORIAL_GAME_DESCRIPTIONS[currentIndex]);
	ui.TutorialGameName->setText(TutorialConstants::TUTORIAL_GAME_NAMES[currentIndex]);
	connect(ui.ReturnToGame, &QPushButton::clicked, this, &QDialog::close);
    connect(ui.ReturnToGame, &QPushButton::pressed, this, &TutorialDialog::buttonPress);
    connect(ui.ReturnToGame, &QPushButton::released, this, &TutorialDialog::buttonRelease);
    ui.ReturnToGame->installEventFilter(this);
}


bool TutorialDialog::eventFilter(QObject* watched, QEvent* event) {
    QPushButton* btn = static_cast<QPushButton*>(watched);

    if (btn && btn->isEnabled()) {

        if (event->type() == QEvent::Enter) {
            ColorUtils::changeColor(btn, ColorConstants::TUTORIAL_BUTTON_LIT_COLOR);
        }

        else if (event->type() == QEvent::Leave) {
            ColorUtils::changeColor(btn, ColorConstants::TUTORIAL_BUTTON_DEFAULT_COLOR);
        }
    }

    return QDialog::eventFilter(watched, event);
}

TutorialDialog::~TutorialDialog()
{
}

void TutorialDialog::buttonPress() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    ColorUtils::changeColor(button, ColorConstants::TUTORIAL_BUTTON_PRESS_COLOR);
}

void TutorialDialog::buttonRelease() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button->isEnabled()) {
        ColorUtils::changeColor(button, ColorConstants::TUTORIAL_BUTTON_LIT_COLOR);
    }
}