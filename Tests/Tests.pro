QT += testlib
QT += gui
QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

HEADERS += \
    ../PuzzleGames/Model/ColorUtils.h
    ../PuzzleGames/Model/ArrayUtils.h

SOURCES +=  \
    ../PuzzleGames/Model/ColorUtils.cpp \
    Tests.cpp \
    ../PuzzleGames/Model/ArrayUtils.cpp


