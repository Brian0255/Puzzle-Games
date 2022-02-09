#pragma once

#include <QPushButton>
#include <QMouseEvent>

class QDifferentClicksButton : public QPushButton {
    Q_OBJECT

public:
    explicit QDifferentClicksButton(QWidget* parent = 0);

private slots:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
signals:
    void rightClicked();
    void leftClicked();
    void middleClicked();
    void leftReleased();
public slots:

};

