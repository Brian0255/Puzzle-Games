#include "ColorUtils.h"
#include"qregularexpression.h"

void ColorUtils::changeTextColor(QWidget* mbutton, const QString color) {
    QString sheet = mbutton->styleSheet();
    QRegularExpression re = QRegularExpression("[^-](color.*?;)");
    QRegularExpressionMatch match = re.match(sheet);
    sheet.replace(match.capturedStart(1), match.capturedLength(1), color);
    mbutton->setStyleSheet(sheet);
}

void ColorUtils::changeColor(QWidget* mbutton, const QString color) {
    mbutton->ensurePolished();
    QString sheet = mbutton->styleSheet();
    QRegularExpression re = QRegularExpression("background-color.*?;");
    sheet.replace(re, color);
    mbutton->setStyleSheet(sheet);
}

QString ColorUtils::getColor(QWidget* mbutton) {
    mbutton->ensurePolished();
    QString sheet = mbutton->styleSheet();
    QRegularExpression re = QRegularExpression("background-color.*?;");
    QRegularExpressionMatch match = re.match(sheet);
    if (match.hasMatch()) {
        return match.captured(0);
    }
    return "";
}