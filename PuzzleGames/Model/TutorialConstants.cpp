#include "TutorialConstants.h"

/*
the index used to subscript these arrays is based on the current index in the game stacked widget
0 = minesweeper, 1 = battleship, etc.
*/

const std::array<QString, TutorialConstants::TOTAL_NUM_GAMES> TutorialConstants::TUTORIAL_GAME_NAMES = {
	"Minesweeper","Battleship","Fill the Squares","Block Slide","Block Fill","Coordination"
};

const std::array<QString, TutorialConstants::TOTAL_NUM_GAMES> TutorialConstants::TUTORIAL_GAME_DESCRIPTIONS = {
	"In this game, you are trying to uncover every tile that is not a bomb.",
	"In this game, you are trying to find every square that is a \"ship.\"",
	"In this game, you must find one continuous path to fill every square.",
	"In this game, you are trying to \"slide\" blocks to fill the red X's.",
	"In this game, you must fill in the designated area with the blocks.",
	"In this game, you are trying to put a block on every blue X."
};