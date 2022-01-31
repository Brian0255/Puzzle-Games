#include "BlockSlideConstants.h"

std::vector<BlockSlideLayout> createLayouts() {
	std::vector<BlockSlideLayout> layouts;
	BlockSlideLayout layout1;
	BlockSlideLayout layout2;
	BlockSlideLayout layout3;
	BlockSlideLayout layout4;
	BlockSlideLayout layout5;
	BlockSlideLayout layout6;
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
	layouts = { layout6 };
	return layouts;
}

const std::vector<BlockSlideLayout> BlockSlideConstants::layouts = createLayouts();
