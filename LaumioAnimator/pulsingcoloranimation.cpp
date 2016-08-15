#include "pulsingcoloranimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> PulsingColorAnimation::factory() {
    return std::unique_ptr <Animation> (new PulsingColorAnimation());
}

PulsingColorAnimation::PulsingColorAnimation(QObject * parent) : Animation("PulsingColor", parent) {
}

bool PulsingColorAnimation::animationStart(Laumio &laumio) {
    (this->*pulse_signal)(0.0);
    laumio.send_color(color());
    return true;
}

bool PulsingColorAnimation::animationUpdate(Laumio &laumio, double time) {
    (this->*pulse_signal)(time);
    laumio.send_color(color());
    return true;
}

void PulsingColorAnimation::animationStop(Laumio &laumio) {
    laumio.send_color(Qt::black);
}

void PulsingColorAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("lower_color") and obj.contains("higher_color")) {
        QRgb lowerColor = QColor(obj["lower_color"].toString()).rgb();
        QRgb higherColor = QColor(obj["higher_color"].toString()).rgb();
        set_meanColor((higherColor + lowerColor) / 2);
        set_varColor((higherColor - lowerColor) / 2);
    }
    if (obj.contains("frequency")) set_pulsation(obj["frequency"].toDouble() * M_PI);
    if (obj.contains("delay")) set_delay(obj["delay"].toDouble());
    if (obj.contains("signal")) set_signal(obj["signal"].toString());
}

void PulsingColorAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    QColor lowerColor(meanColor() - varColor());
    obj["lower_color"] = lowerColor.name();
    QColor higherColor(meanColor() + varColor());
    obj["higher_color"] = higherColor.name();
    obj["frequency"] = pulsation() / (2 * M_PI);
    obj["delay"] = delay();
    obj["signal"] = signalName();
}


void PulsingColorAnimation::set_signal(QString name) {
    if (name == "sinus") {
        pulse_signal = &PulsingColorAnimation::sinus_signal;
    } else {
        name = "sinus";
        pulse_signal = &PulsingColorAnimation::sinus_signal;
    }
    m_signalName = name;
}

void PulsingColorAnimation::sinus_signal(double time) {
    color().setRgb(meanColor() + varColor() * std::sin(pulsation() * (time - delay())));
}
