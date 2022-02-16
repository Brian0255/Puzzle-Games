#pragma once

#include <QDialog>
#include "ui_TutorialDialog.h"

class TutorialDialog : public QDialog
{
	Q_OBJECT

public:
	TutorialDialog(int currentIndex, QWidget *parent = Q_NULLPTR);
	~TutorialDialog();
	bool eventFilter(QObject* watched, QEvent* event);
public slots:
	void buttonPress();
	void buttonRelease();
private:
	Ui::TutorialDialog ui;
	int currentIndex;
};
