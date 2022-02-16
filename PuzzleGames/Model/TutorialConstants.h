#pragma once
#include<array>
#include<qstring.h>
class TutorialConstants {
public:
	const static int TOTAL_NUM_GAMES{ 6 };
	const static std::array<QString, TOTAL_NUM_GAMES> TUTORIAL_GAME_NAMES;
	const static std::array<QString, TOTAL_NUM_GAMES> TUTORIAL_GAME_DESCRIPTIONS;
};

