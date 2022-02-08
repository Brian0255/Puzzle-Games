#pragma once
#include<qstring.h>
#include<qwidget.h>
class Utilities {
public:
	static void changeColor(QWidget* mbutton, const QString color);
	static QString getColor(QWidget* mbutton);

	template<int size>
	static std::array<int, size> subtractIntArrays(std::array<int, size> operator1, std::array<int, size> operator2);

	template<int size>
	static std::array<int, size> addIntArrays(std::array<int, size> operator1, std::array<int, size> operator2);
};

template<int size>
inline std::array<int, size> Utilities::subtractIntArrays(std::array<int, size> operator1, std::array<int, size> operator2) {
	std::array<int, size> result{};
	for (int i = 0; i < operator1.size(); ++i) {
		result[i] = (operator1[i] - operator2[i]);
	}
	return result;
}

template<int size>
inline std::array<int, size> Utilities::addIntArrays(std::array<int, size> operator1, std::array<int, size> operator2) {
	std::array<int, size> result{};
	for (int i = 0; i < operator1.size(); ++i) {
		result[i] = (operator1[i] + operator2[i]);
	}
	return result;
}
