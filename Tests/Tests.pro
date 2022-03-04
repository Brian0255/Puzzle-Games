QT += testlib
QT += gui
QT += widgets

CONFIG += console

TEMPLATE = app

SUBDIRS += \
    ../PuzzleGames/Controller \
    ../PuzzleGames/Model/Battleship \
    ../PuzzleGames/View \
    ../PuzzleGames/x64/Release/uic

HEADERS += \
    ../PuzzleGames/Model/ColorUtils.h \
    ../PuzzleGames/Model/ArrayUtils.h \
    ../PuzzleGames/x64/Release/uic/ui_PuzzleGames.h

SOURCES +=  \
    ../PuzzleGames/Model/ColorUtils.cpp \
    Tests.cpp \
    ../PuzzleGames/Model/ArrayUtils.cpp


