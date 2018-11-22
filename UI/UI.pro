#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T13:53:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IslandGame
TEMPLATE = app
CONFIG += c++14


SOURCES += main.cc \
    mainwindow.cpp \
    graphichex.cpp \
    gameboard.cpp \
    player.cpp \
    gamestate.cpp \
    graphicpawn.cpp \
    openingdialog.cpp \
    mainuiwindow.cpp

HEADERS  += \
    gameboard.hh \
    player.hh \
    gamestate.hh \
    mainwindow.hh \
    graphichex.hh \
    graphicpawn.hh \
    openingdialog.hh \
    mainuiwindow.hh

INCLUDEPATH += $$PWD/../GameLogic/Engine
DEPENDPATH += $$PWD/../GameLogic/Engine

CONFIG(release, debug|release) {
   DESTDIR = release
}

CONFIG(debug, debug|release) {
   DESTDIR = debug
}

LIBS += -L$$OUT_PWD/../GameLogic/Engine
LIBS += -L$$OUT_PWD/../GameLogic/Engine/$${DESTDIR}/ -lEngine

 win32 {
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILE(S) for Windows &
    copyfiles.commands += @echo from \"$$_PRO_FILE_PWD_/../GameLogic/Assets\" to  \"$$OUT_PWD\" &
    copyfiles.commands += @call xcopy \"$$_PRO_FILE_PWD_/../GameLogic/Assets\" \"$$OUT_PWD//Assets\" /i /s /e /y
}
unix:!macx {
    copyfiles.commands += echo \"NOW COPYING ADDITIONAL FILE(S) for Linux\" &&
    copyfiles.commands += echo from $$_PRO_FILE_PWD_/../GameLogic/Assets to  $$OUT_PWD &
    copyfiles.commands += cp -r $$_PRO_FILE_PWD_/../GameLogic/Assets $$DESTDIR
}
 macx {
    copyfiles.commands += @echo \"NOW COPYING ADDITIONAL FILE(S) for MacOS\" &&
    copyfiles.commands += echo from $$_PRO_FILE_PWD_/../GameLogic/Assets to  $$OUT_PWD &
    copyfiles.commands += mkdir -p $$DESTDIR/IslandGame.app/Contents/MacOS &&
    copyfiles.commands += cp -r $$_PRO_FILE_PWD_/../GameLogic/Assets $$DESTDIR &&
    copyfiles.commands += cp -r $$_PRO_FILE_PWD_/../GameLogic/Assets $$DESTDIR/IslandGame.app/Contents/MacOS/
 }

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

FORMS += \
    openingdialog.ui \
    mainuiwindow.ui
