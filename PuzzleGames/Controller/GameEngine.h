#pragma once
#include<qobject.h>
class GameEngine : public QObject {
	Q_OBJECT

signals:
	void sendTopLeftLabelUpdate(QString newText);
	void sendTopRightLabelUpdate(QString newText);
	void sendStatusLabelUpdate(QString newText);

public:
	virtual bool startEngine() = 0;
	virtual bool resetGame() = 0;

	bool eventFilter(QObject* watched, QEvent* event);

private:
	virtual void setupTiles() = 0;
};

