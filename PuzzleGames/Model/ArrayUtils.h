#pragma once
#include<qstring.h>
#include<qwidget.h>
class ArrayUtils {
public:


	template<int size>
	static std::array<int, size> subtractIntArrays(std::array<int, size> operator1, std::array<int, size> operator2);

	template<int size>
	static std::array<int, size> addIntArrays(std::array<int, size> operator1, std::array<int, size> operator2);
};

template<int size>
inline std::array<int, size> ArrayUtils::subtractIntArrays(std::array<int, size> operator1, std::array<int, size> operator2) {
	std::array<int, size> result{};
	for (int i = 0; i < operator1.size(); ++i) {
		result[i] = (operator1[i] - operator2[i]);
	}
	return result;
}

template<int size>
inline std::array<int, size> ArrayUtils::addIntArrays(std::array<int, size> operator1, std::array<int, size> operator2) {
	std::array<int, size> result{};
	for (int i = 0; i < operator1.size(); ++i) {
		result[i] = (operator1[i] + operator2[i]);
	}
	return result;
}
