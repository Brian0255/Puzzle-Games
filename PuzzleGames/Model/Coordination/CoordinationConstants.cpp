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
	layouts = { layout1 };
	return layouts;
}

const std::vector<GameLayout<7>> CoordinationConstants::layouts = createLayouts();