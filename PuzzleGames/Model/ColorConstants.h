#pragma once
#include<qstring.h>
#include<map>
class ColorConstants {
public:
	static const QString DARK_BUTTON_DEFAULT_COLOR;
	static const QString DARK_BUTTON_LIT_COLOR;
	static const QString DARK_BUTTON_PRESS_COLOR;

	static const QString TUTORIAL_BUTTON_DEFAULT_COLOR;
	static const QString TUTORIAL_BUTTON_LIT_COLOR;
	static const QString TUTORIAL_BUTTON_PRESS_COLOR;

	static const QString TILE_DEFAULT_COLOR;
	static const QString TILE_HOVER_COLOR;
	static const QString TILE_PRESS_COLOR;
	static const QString TILE_UNCOVERED_COLOR;

	static const QString HIT_SHIP_COLOR;
	static const QString HIT_PART_OF_SHIP_COLOR;
	static const QString BATTLESHIP_CROSS_OFF_COLOR;

	static const QString MINESWEEPER_HIT_BOMB_COLOR;

	static const QString FILL_SQUARES_FILL_COLOR;
	static const QString FILL_SQUARES_HEAD_COLOR;
	static const QString FILL_SQUARES_BEFORE_HEAD_COLOR;
	static const QString FILL_SQUARES_X_COLOR;

	static const QString BLOCK_SLIDE_HIGHLIGHT_COLOR;
	static const QString BLOCK_SLIDE_BLOCK_COLOR;
	static const QString BLOCK_SLIDE_BARRIER_COLOR;
	static const QString BLOCK_SLIDE_DEFAULT_COLOR;
	static const QString BLOCK_SLIDE_BLOCK_HOVER_COLOR;
	static const QString BLOCK_SLIDE_BLOCK_PRESS_COLOR;

	static const QString BLOCK_FILL_DEFAULT_TILE_COLOR;
	static const QString BLOCK_FILL_OVERLAP_ERROR_COLOR;
	static const QString BLOCK_FILL_MAIN_GRID_TILE_COLOR;
	static const QString BLOCK_FILL_BARRIER_COLOR;
	static const QString BLOCK_FILL_GOAL_TILE_COLOR;

	static const std::map<QChar, QString> BLOCK_FILL_PIECE_COLORS;
	static const std::map<QChar, QString> BLOCK_FILL_PIECE_HIGHLIGHT_COLORS;

	static const QString COORDINATION_BLOCK_COLOR;
	static const QString COORDINATION_BLOCK_HOVER_COLOR;
	static const QString COORDINATION_BLOCK_PRESS_COLOR;
	static const QString COORDINATION_DEFAULT_COLOR;
	static const QString COORDINATION_BARRIER_COLOR;
};