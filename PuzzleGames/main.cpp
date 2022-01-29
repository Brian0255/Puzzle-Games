#include "PuzzleGames.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PuzzleGames w;
    w.show();
    return a.exec();
}
