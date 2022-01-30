#include "QDifferentClicksButton.h"

QDifferentClicksButton::QDifferentClicksButton(QWidget* parent) :
    QPushButton(parent) {
}

void QDifferentClicksButton::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::RightButton)
        emit rightClicked();
    else if (e->button() == Qt::LeftButton) {
        emit leftClicked();
    }
    else if (e->button() == Qt::MiddleButton)
        emit middleClicked();
}