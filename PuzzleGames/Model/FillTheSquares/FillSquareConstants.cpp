#include "FillSquareConstants.h"

std::vector<FillSquareLayout> createLayouts() {
	std::vector<FillSquareLayout> layouts;
	FillSquareLayout layout1;
	FillSquareLayout layout2;
	FillSquareLayout layout3;
	FillSquareLayout layout4;
	FillSquareLayout layout5;
	FillSquareLayout layout6;
	FillSquareLayout layout7;
	FillSquareLayout layout8;
	FillSquareLayout layout9;
	FillSquareLayout layout10;
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


const std::vector<FillSquareLayout> FillSquareConstants::layouts = createLayouts();
