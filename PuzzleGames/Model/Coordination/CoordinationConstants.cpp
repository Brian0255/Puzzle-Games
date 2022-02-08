#include"CoordinationConstants.h"

std::vector<CoordinationLayout> createLayouts() {
	std::vector<CoordinationLayout> layouts;
	CoordinationLayout layout1;
	CoordinationLayout layout2;
	CoordinationLayout layout3;
	CoordinationLayout layout4;
	CoordinationLayout layout5;
	CoordinationLayout layout6;
	CoordinationLayout layout7;
	CoordinationLayout layout8;
	CoordinationLayout layout9;
	CoordinationLayout layout10;
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

const std::vector<CoordinationLayout> CoordinationConstants::layouts = createLayouts();