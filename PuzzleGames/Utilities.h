#pragma once
#include<qstring.h>
#include<qwidget.h>
class Utilities {
public:
	static void changeColor(QWidget* mbutton, const QString color);
	static QString getColor(QWidget* mbutton);
};

