TEMPLATE = app

QT += qml quick multimedia
CONFIG += c++11

SOURCES += main.cpp \
    laumio.cpp \
    laumioanimation.cpp \
    signals/signal.cpp \
    signals/nullsignal.cpp \
    signals/sumsignal.cpp \
    signals/slopesignal.cpp \
    animations/animation.cpp \
    animations/constantcoloranimation.cpp \
    animations/pulsingcoloranimation.cpp \
    animations/progressivecoloranimation.cpp \
    animations/boundedpulsingcoloranimation.cpp \
    animations/mix2colorsanimation.cpp

RESOURCES += qml/qml.qrc

include(deployment.pri)

HEADERS += \
    laumio.h \
    laumioanimation.h \
    macrodegeu.h \
    signals/signal.h \
    signals/nullsignal.h \
    signals/sumsignal.h \
    signals/slopesignal.h \
    animations/animation.h \
    animations/constantcoloranimation.h \
    animations/pulsingcoloranimation.h \
    animations/progressivecoloranimation.h \
    animations/boundedpulsingcoloranimation.h \
    animations/mix2colorsanimation.h
