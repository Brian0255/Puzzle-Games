#include "Utilities.h"
#include"qregularexpression.h"

void Utilities::changeColor(QWidget* mbutton, const QString color) {
    mbutton->ensurePolished();
    QString sheet = mbutton->styleSheet();
    QRegularExpression re = QRegularExpression("background-color.*?;");
    sheet.replace(re, color);
    mbutton->setStyleSheet(sheet);
}

QString Utilities::getColor(QWidget* mbutton) {
    mbutton->ensurePolished();
    QString sheet = mbutton->styleSheet();
    QRegularExpression re = QRegularExpression("background-color.*?;");
    QRegularExpressionMatch match = re.match(sheet);
    if (match.hasMatch()) {
        return match.captured(0);
    }
    return "";
}
