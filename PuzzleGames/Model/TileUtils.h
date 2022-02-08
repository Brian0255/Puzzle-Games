#pragma once 
#include<array>
class TileUtils {
public:
	template<typename T, int size>
	static void enableButtons(std::array<T, size>& tiles);
	
	template<typename T, int size>
	static void disableButtons(std::array<T, size>& tiles); 
};

template<typename T, int size>
inline void TileUtils::enableButtons(std::array<T, size>& tiles) {
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			tile.button->setEnabled(true);
		}
	}
}

template<typename T, int size>
inline void TileUtils::disableButtons(std::array<T, size>& tiles) {
	for (auto& tileArray : tiles) {
		for (auto& tile : tileArray) {
			tile.button->setEnabled(true);
		}
	}
}
