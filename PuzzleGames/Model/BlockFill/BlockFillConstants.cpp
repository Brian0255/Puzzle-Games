#include"BlockFillConstants.h"
/*
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------",
"----------------"
*/

std::vector<GameLayout<16>> createLayouts() {
	std::vector<GameLayout<16>> layouts;
	GameLayout<16> layout1;
	GameLayout<16> layout2;
	GameLayout<16> layout3;
	GameLayout<16> layout4;
	GameLayout<16> layout5;
	GameLayout<16> layout6;
	GameLayout<16> layout7;
	GameLayout<16> layout8;
	GameLayout<16> layout9;
	GameLayout<16> layout10;
	layout1.layout = {
	"-------|o11-o22-",
	"-------|-11--22-",
	"-------|--------",
	"-------|t333----",
	"--B----|--3-----",
	"--BGGG-|--------",
	"-GBGGGG|s44-z55-",
	"-GBGGGG|44----55",
	"-GGGGGG|--------",
	"-GGGGG-|j6l7-i8-",
	"-GGGGG-|-6-7--8-",
	"----GG-|66-77-8-",
	"----G--|------8-",
	"-------|--------",
	"-------|--------",
	"-------|--------"
	};
	layout2.layout = {
	"-------|t111-t2-",
	"-------|--1--222",
	"-------|--------",
	"-------|t333j4--",
	"BGGGGGG---3--4--",
	"GBGGGBGj5---44--",
	"GGGGGGG-555---z7",
	"GGBGBGG-------77",
	"GGGBGGGz66----7-",
	"GBGGGBG--66-----",
	"BGGGGGG---------",
	"-------|z99--jAA",
	"-------|--99--A-",
	"-------|------A-",
	"-------|i8888---",
	"-------|--------"
	};
	layout3.layout = {
	"---------l1-l22-",
	"----------1---2-",
	"----GGG---11--2-",
	"----GGG-t333t4--",
	"-G--GBG---3-444-",
	"-GG-GBG---------",
	"-GG-GGG-i5555i6-",
	"GGG-GGG-------6-",
	"---------s77--6-",
	"----GG---77---6-",
	"--GGGG-----lA---",
	"--GGBGG-----A---",
	"---GGGG-----AA--",
	"---GG-----------",
	"--------t999-l8-",
	"----------9-888-",
	};
	layout4.layout = {
	"--------t111t2--",
	"---GGGGG--1-222-",
	"--GGGGGGG-------",
	"-GGGGBGGGGl333--",
	"----GGG----3t4--",
	"-GGGGBGGGG--44--",
	"--GGGGGGG-t5-4--",
	"---GG-GG--555l6-",
	"----G-G-------6-",
	"----------s77-66",
	"-z9--z88--77----",
	"-99----88-------",
	"-9--------------",
	"--oAAtDDD-------",
	"---AA--D--------",
	"----------------"
	};
	layout5.layout = {
	"-------------t2-",
	"-BGGGGGBBz11--22",
	"-GBGGGGGG--11-2-",
	"-GGBGGGGG-------",
	"-GGGGBGGBj333-j4",
	"-BGGGBGGB---3--4",
	"-GGBBBGGG-----44",
	"-GGGBGGGG-s55s6-",
	"-BGGGGGGB-55--66",
	"--------j9-----6",
	"-o77t888-999tA--",
	"--77--8-----AAA-",
	"jC--------------",
	"-CCCzD----------",
	"----DD----------",
	"----D-----------"
	};
	layout6.layout = {
	"----------------",
	"-GGGGGGGGGt1----",
	"-GBGBGBBBG-11t2-",
	"-GGBGGGBBG-1-22-",
	"-GBBBGBBGG----2-",
	"-GGBGGGGGGt3----",
	"-GBBBGBGBG-33t4-",
	"-GGGGGGGGG-3-44-",
	"--------------4-",
	"-i5555l6l77-----",
	"-------6--7--jA-",
	"i8i9---66-7---A-",
	"-8-9---------AA-",
	"-8-9--jCCC------",
	"-8-9-----C------",
	"----------------"
	};
	layout7.layout = {
	"-------GG-------",
	"-o22---GG--o11--",
	"--22---GG---11--",
	"------GGGG------",
	"---GGGGGGGGGG---",
	"---GGGGGGGGGG---",
	"------GGGG------",
	"-o33---GG---z4--",
	"--33---GG---44--",
	"-------GG---4---",
	"-z5-z6----------",
	"-55-66i8l9-jAA--",
	"-5--6--8-9--A---",
	"-------8-99-A---",
	"-i7777-8--------",
	"----------------"
	};
	layout8.layout = {
	"j5j66----z77--z8",
	"-5-6---G---77-88",
	"55-6--GGG-----8-",
	"-----GGGGG------",
	"t9---GGGGGG---tA",
	"99--GGGGGGGG--AA",
	"-9--GGGGGGGGG--A",
	"---BBBBBBBBBBB--",
	"-------B--------",
	"-BBBBBBBBBBBBB--",
	"--GGGGGGGGGGG-zE",
	"---GGGGGGGGG--EE",
	"jC------------E-",
	"-CCC--tDDD---l44",
	"--------D--o33-4",
	"i1111i2222--33-4"
	};
	layout9.layout = {
	"-t111------o22--",
	"---1--BGG---22--",
	"j333---BGGG--l55",
	"---3t4--BGGG---5",
	"t7--444--BGGG--5",
	"777-------BGGt6-",
	"---t8o99--BGG-66",
	"-B-88-99-BBGG-6-",
	"-GB-8---BGGGG---",
	"-GGB---BGGGG-lF--",
	"-GGGBBBGGGGG--F-",
	"--GGGGGGGGG---FF",
	"zC-GGGGGGG------",
	"CC---GGGG-zD-sE-",
	"C---------DD--EE",
	"iAAAA-----D----E"
	};
	layout10.layout = {
	"GGGG-s11----GGGG",
	"GGGG-11j222-GGGG",
	"GGGG------2-GGGG",
	"GGGG-l3l44--GGGG",
	"------3--4------",
	"j55---33-4--l66-",
	"-5-t7i8888t9--6-",
	"-5-777----999-6-",
	"----------------",
	"jA--oCC-oDD--lE-",
	"-AAA-CC--DD-EEE-",
	"----------------",
	"GGGG-zF-sH--GGGG",
	"GGGG-FF--HH-GGGG",
	"GGGG-F----H-GGGG",
	"GGGG-iIIII--GGGG"
	};
	layouts = { layout1, layout2, layout3, layout4, layout5,
		layout6, layout7, layout8, layout9, layout10 };
	return layouts;
}

const std::vector<GameLayout<16>> BlockFillConstants::layouts = createLayouts();
const std::array<QChar, 7> BlockFillConstants::pieceNames = {
	'o','l','j','t','s','z','i'
};