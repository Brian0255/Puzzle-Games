#pragma once
#include<qstring.h>
#include<qwidget.h>
class ColorUtils {
public:
	static void changeTextColor(QWidget* mbutton, const QString color);
	static void changeColor(QWidget* mbutton, const QString color);
	static QString getColor(QWidget* mbutton);
};

