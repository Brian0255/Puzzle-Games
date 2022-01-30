#pragma once
#include<qobject.h>
class GameEngine : public QObject {
	Q_OBJECT
signals:
	void sendTopLeftLabelUpdate(QString newText);
	void sendTopRightLabelUpdate(QString newText);
	void sendStatusLabelUpdate(QString newText);

public:
	virtual void startEngine();
	virtual void resetGame();
	GameEngine();
	virtual ~GameEngine();
	virtual bool eventFilter(QObject* watched, QEvent* event);
};

