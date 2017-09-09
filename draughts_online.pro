######################################################################
# Automatically generated by qmake (3.1) Wed Sep 6 16:15:20 2017
######################################################################

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = draughts_online
TEMPLATE = app

SOURCES += \
#    main.cpp\
#    mainwindow.cpp \
#    logic/game.cpp \
#    client/client.cpp \
#    test/simpleserver.cpp \
#    UI/welcome.cpp \
#    main.cpp \
#    UI/draughtsboard.cpp \
    UI/piecebtn.cpp \
    test/testpiecebtn.cpp \
    test/test.cpp \
    UI/icons.cpp

HEADERS  += \
#    mainwindow.h \
#    logic/game.h \
    logic/piece.h \
#    client/client.h \
#    client/message.h \
#    test/testgame.h \
#    test/testnetwork.h \
#    test/simpleserver.h \
#    UI/welcome.h \
#    UI/draughtsboard.h \
    UI/piecebtn.h \
    test/testpiecebtn.h \
    UI/icons.h

FORMS    += \
#        mainwindow.ui \
#    client/client.ui \
#    UI/welcome.ui \
#    UI/draughtsboard.ui \
    test/testpiecebtn.ui

INCLUDEPATH += \
        ./logic \
        ./client \
        ./UI \
        ./test

# Directories

RESOURCES += \
    resources.qrc
