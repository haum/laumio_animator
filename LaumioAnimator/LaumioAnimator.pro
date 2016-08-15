TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    laumio.cpp \
    laumioanimation.cpp \
    animation.cpp \
    constantcoloranimation.cpp

RESOURCES += qml.qrc

include(deployment.pri)

HEADERS += \
    laumio.h \
    laumioanimation.h \
    animation.h \
    constantcoloranimation.h \
    macrodegeu.h
