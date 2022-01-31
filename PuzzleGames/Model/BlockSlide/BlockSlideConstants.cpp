#include "BlockSlideConstants.h"

std::vector<BlockSlideLayout> createLayouts() {
	std::vector<BlockSlideLayout> layouts;
	BlockSlideLayout layout1;
	BlockSlideLayout layout2;
	BlockSlideLayout layout3;
	BlockSlideLayout layout4;
	BlockSlideLayout layout5;
	BlockSlideLayout layout6;
	BlockSlideLayout layout7;
	BlockSlideLayout layout8;
	BlockSlideLayout layout9;
	BlockSlideLayout layout10;
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

const std::vector<BlockSlideLayout> BlockSlideConstants::layouts = createLayouts();
