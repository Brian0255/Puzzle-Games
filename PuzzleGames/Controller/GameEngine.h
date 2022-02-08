#pragma once
#include<qobject.h>
class GameEngine : public QObject {
	Q_OBJECT

signals:
	void sendTopLeftLabelUpdate(QString newText);
	void sendTopRightLabelUpdate(QString newText);
	void sendStatusLabelUpdate(QString newText);

public:
	virtual void startEngine() = 0;
	virtual void resetGame() = 0;

	virtual void setupTiles() = 0;

	bool eventFilter(QObject* watched, QEvent* event);
};

