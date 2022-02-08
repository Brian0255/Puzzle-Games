#include "FillSquareConstants.h"

std::vector<GameLayout<8>> createLayouts() {
	std::vector<GameLayout<8>> layouts;
	GameLayout<8> layout1;
	GameLayout<8> layout2;
	GameLayout<8> layout3;
	GameLayout<8> layout4;
	GameLayout<8> layout5;
	GameLayout<8> layout6;
	GameLayout<8> layout7;
	GameLayout<8> layout8;
	GameLayout<8> layout9;
	GameLayout<8> layout10;
	layout1.layout = {
		"--XX--XX",
		"--------",
		"-X--XXX-",
		"----X---",
		"-X------",
		"XX------",
		"--------",
		"-----XXX"
	};
	layout2.layout = {
		"XXXXX--X",
		"XXXX---X",
		"--X--X-X",
		"----X--X",
		"--------",
		"-XX--X--",
		"-X---X-X",
		"-X-----X"
	};
	layout3.layout = {
		"--------",
		"-X----X-",
		"---X--X-",
		"XX------",
		"----XX--",
		"-XX-XXX-",
		"--------",
		"------XX"
	};
	layout4.layout = {
		"----X---",
		"---X----",
		"-XX-----",
		"-X----X-",
		"-----X--",
		"----X--X",
		"---XX---",
		"XX------"
	};
	layout5.layout = {
		"-----X--",
		"-----X--",
		"-XX-----",
		"-XXXX---",
		"--X---XX",
		"--X-X---",
		"----X---",
		"------XX"
	};
	layout6.layout = {
		"--XXXX--",
		"--------",
		"-X----X-",
		"-X-XX-X-",
		"-XX--XX-",
		"--------",
		"--------",
		"--------"
	};
	layout7.layout = {
		"XX------",
		"---X--X-",
		"--XX----",
		"X--XX--X",
		"X--XX--X",
		"----XX--",
		"-X--X---",
		"------XX"
	};
	layout8.layout = {
		"----XX--",
		"---XX---",
		"--------",
		"-X--XX-X",
		"---X--XX",
		"--------",
		"----X---",
		"--X-----"
	};
	layout9.layout = {
		"------X-",
		"-XX--X--",
		"----XX--",
		"----XX--",
		"---XXX--",
		"----XX--",
		"--X----X",
		"XXXX--XX"
	};
	layout10.layout = {
		"X----X--",
		"--XX----",
		"-----X--",
		"--XX----",
		"X---XX--",
		"--X----X",
		"----XX--",
		"--X-----"
	};
	layouts = { layout1, layout2, layout3, layout4, layout5,
				layout6, layout7, layout8, layout9, layout10};
	return layouts;
}


const std::vector<GameLayout<8>> FillSquareConstants::layouts = createLayouts();
