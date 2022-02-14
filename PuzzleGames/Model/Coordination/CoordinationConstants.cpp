#include"CoordinationConstants.h"
std::vector<GameLayout<7>> createLayouts() {
	std::vector<GameLayout<7>> layouts;
	GameLayout<7> layout1;
	GameLayout<7> layout2;
	GameLayout<7> layout3;
	GameLayout<7> layout4;
	GameLayout<7> layout5;
	GameLayout<7> layout6;
	GameLayout<7> layout7;
	GameLayout<7> layout8;
	GameLayout<7> layout9;
	GameLayout<7> layout10;
	layout1.layout = {
	"BB--G--",
	"-------",
	"------G",
	"-------",
	"-------",
	"-X-----",
	"-------"
	};
	layout2.layout = {
	"B-----B",
	"----G--",
	"-XG--X-",
	"---XG--",
	"-XG--X-",
	"-------",
	"B-----B"
	};
	layout3.layout = {
	"---B---",
	"B-----B",
	"-BGGG--",
	"B-GGGX-",
	"--GGG--",
	"---B-B-",
	"-B----B"
	};
	layout4.layout = {
	"-BBBBB-",
	"-------",
	"-------",
	"-G-X-G-",
	"--G-G--",
	"---G---",
	"-------"
	};
	layout5.layout = {
	"G------",
	"G------",
	"G--BB--",
	"--BBBB-",
	"G--X---",
	"G------",
	"G------"
	};
	layout6.layout = {
	"--GX--G",
	"XB-XX--",
	"---X--B",
	"XXXXXXX",
	"---XXX-",
	"-B-XX--",
	"GX-X-BG"
	};
	layout7.layout = {
	"-------",
	"GGXXX--",
	"---BB--",
	"-------",
	"--BB---",
	"--XXX--",
	"-----GG"
	};
	layout8.layout = {
	"B---X-G",
	"B-X---G",
	"B---X-G",
	"B-----G",
	"B-X---G",
	"B----XG",
	"B-X---G"
	};
	layout9.layout = {
	"-------",
	"-X-X-X-",
	"--G-G--",
	"-X-X-X-",
	"--G-G--",
	"-X-X-X-",
	"---BBBB"
	};
	layout10.layout = {
	"---B---",
	"-------",
	"-X-G-X-",
	"B-GGG-B",
	"-X-G-X-",
	"-------",
	"B--B---"
	};
	layouts = { layout1, layout2, layout3, layout4, layout5, layout6, layout7, layout8, layout9, layout10 };
	return layouts;
}

const std::vector<GameLayout<7>> CoordinationConstants::layouts = createLayouts();