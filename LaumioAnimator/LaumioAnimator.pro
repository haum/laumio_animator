TEMPLATE = app

QT += qml quick multimedia
CONFIG += c++11

SOURCES += main.cpp \
    laumio.cpp \
    laumioanimation.cpp \
    animation.cpp \
    constantcoloranimation.cpp \
    pulsingcoloranimation.cpp \
    progressivecoloranimation.cpp \
    boundedpulsingcoloranimation.cpp

RESOURCES += qml/qml.qrc

include(deployment.pri)

HEADERS += \
    laumio.h \
    laumioanimation.h \
    animation.h \
    constantcoloranimation.h \
    pulsingcoloranimation.h \
    progressivecoloranimation.h \
    macrodegeu.h \
    boundedpulsingcoloranimation.h
