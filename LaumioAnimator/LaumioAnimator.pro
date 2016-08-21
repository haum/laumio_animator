TEMPLATE = app

QT += qml quick multimedia
CONFIG += c++11

SOURCES += main.cpp \
    laumio.cpp \
    laumioanimation.cpp \
    animations/animation.cpp \
    animations/constantcoloranimation.cpp \
    animations/pulsingcoloranimation.cpp \
    animations/progressivecoloranimation.cpp \
    animations/boundedpulsingcoloranimation.cpp

RESOURCES += qml/qml.qrc

include(deployment.pri)

HEADERS += \
    laumio.h \
    laumioanimation.h \
    macrodegeu.h \
    animations/animation.h \
    animations/constantcoloranimation.h \
    animations/pulsingcoloranimation.h \
    animations/progressivecoloranimation.h \
    animations/boundedpulsingcoloranimation.h
