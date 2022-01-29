#pragma once
#include<qobject.h>
class GameEngine : public QObject {
	Q_OBJECT
public:
	virtual void startEngine();
	virtual void resetGame();
	GameEngine();
	virtual ~GameEngine();
};

