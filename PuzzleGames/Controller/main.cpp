#include "PuzzleGames.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    PuzzleGames w;
    w.show();
    return a.exec();
}
