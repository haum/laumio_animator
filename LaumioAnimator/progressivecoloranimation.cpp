#include "progressivecoloranimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> ProgressiveColorAnimation::factory() {
    return std::unique_ptr <Animation> (new ProgressiveColorAnimation());
}

ProgressiveColorAnimation::ProgressiveColorAnimation(QObject * parent) : Animation("ProgressiveColor", parent) {
}

bool ProgressiveColorAnimation::animationStart(Laumio &laumio) {
    (this->*slope_signal)(0.0);
    laumio.send_color(color());
    return true;
}

bool ProgressiveColorAnimation::animationUpdate(Laumio &laumio, double time) {
    (this->*slope_signal)(time);
    laumio.send_color(color());
    return true;
}

void ProgressiveColorAnimation::animationStop(Laumio &laumio) {
    laumio.send_color(Qt::black);
}

void ProgressiveColorAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("first_color") and obj.contains("last_color")) {
        set_firstColor(QColor(obj["first_color"].toString()).rgb());
        set_lastColor(QColor(obj["last_color"].toString()).rgb());
    }
    if (obj.contains("signal")) set_signal(obj["signal"].toString());
}

void ProgressiveColorAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    QColor Color1(firstColor());
    obj["first_color"] = Color1.name();
    QColor Color2(lastColor());
    obj["last_color"] = Color2.name();
    obj["signal"] = signalName();
}


void ProgressiveColorAnimation::set_signal(QString name) {
    if (name == "linear") {
        slope_signal = &ProgressiveColorAnimation::linear_signal;
    } else {
        name = "linear";
        slope_signal = &ProgressiveColorAnimation::linear_signal;
    }
    m_signalName = name;
}

void ProgressiveColorAnimation::linear_signal(double time) {
    QRgb newColor = firstColor() + QRgb(time * (lastColor() - firstColor()) / duration());
    m_color.setRgb(newColor);
}
