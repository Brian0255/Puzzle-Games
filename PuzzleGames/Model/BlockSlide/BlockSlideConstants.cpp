#include "BlockSlideConstants.h"

std::vector<GameLayout<6>> createLayouts() {
	std::vector<GameLayout<6>> layouts;
	GameLayout<6> layout1;
	GameLayout<6> layout2;
	GameLayout<6> layout3;
	GameLayout<6> layout4;
	GameLayout<6> layout5;
	GameLayout<6> layout6;
	GameLayout<6> layout7;
	GameLayout<6> layout8;
	GameLayout<6> layout9;
	GameLayout<6> layout10;
	layout1.layout = {
		"B----B",
		"------",
		"---O--",
		"------",
		"------",
		"B-----"
	};
	layout2.layout = {
		"------",
		"----X-",
		"XO--X-",
		"------",
		"------",
		"--B-B-"
	};
	layout3.layout = {
		"B--O-B",
		"-----O",
		"O-----",
		"------",
		"------",
		"-B----"
	};
	layout4.layout = {
		"------",
		"B----O",
		"B-O---",
		"-----B",
		"-----B",
		"-O-O--"
	};
	layout5.layout = {
		"B----B",
		"------",
		"--OO--",
		"--OO--",
		"------",
		"B----B"
	};
	layout6.layout = {
		"----X-",
		"XO--O-",
		"--BB--",
		"--BB--",
		"-O--OX",
		"XX----"
	};
	layout7.layout = {
		"X-----",
		"----X-",
		"-XO---",
		"-XB---",
		"-----X",
		"XX----"
	};
	layout8.layout = {
		"XOOOOO",
		"X-XXXX",
		"BBO---",
		"BBBO--",
		"BBB-O-",
		"XXXXXX"
	};
	layout9.layout = {
		"--O---",
		"------",
		"B-----",
		"-----B",
		"------",
		"---O--"
	};
	layout10.layout = {
		"--O--B",
		"B-----",
		"--O---",
		"B--O--",
		"------",
		"---O-B"
	};
	layouts = { layout1, layout2, layout3, layout4, layout5,
				layout6, layout7, layout8, layout9,layout10 };
	return layouts;
}

const std::vector<GameLayout<6>> BlockSlideConstants::layouts = createLayouts();
