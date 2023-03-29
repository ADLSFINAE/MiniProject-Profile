QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    board.cpp \
    customscene.cpp \
    customview.cpp \
    figures/figures.cpp \
    figures/horse.cpp \
    figures/king.cpp \
    figures/pawn.cpp \
    figures/queen.cpp \
    figures/rook.cpp \
    main.cpp

HEADERS += \
    block.h \
    board.h \
    customscene.h \
    customview.h \
    figures/figures.h \
    figures/horse.h \
    figures/king.h \
    figures/pawn.h \
    figures/queen.h \
    figures/rook.h \
    paramsNdefines.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
