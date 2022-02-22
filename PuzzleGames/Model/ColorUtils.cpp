#include "ColorUtils.h"
#include"qregularexpression.h"

void ColorUtils::changeColor(QWidget* mbutton, const QString color) {
    mbutton->ensurePolished();
    QString sheet = mbutton->styleSheet();
    QRegularExpression re = QRegularExpression("background-color.*?;");
    bool matched = re.match(sheet).hasMatch();
    if (matched) {
        sheet.replace(re, color);
    }
    else {
        sheet += color;
    }
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