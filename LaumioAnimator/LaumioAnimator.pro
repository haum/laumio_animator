TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    laumio.cpp \
    laumioanimation.cpp \
    animation.cpp \
    constantcoloranimation.cpp \
    pulsingcoloranimation.cpp

RESOURCES += qml.qrc

include(deployment.pri)

HEADERS += \
    laumio.h \
    laumioanimation.h \
    animation.h \
    constantcoloranimation.h \
    pulsingcoloranimation.h \
    macrodegeu.h
