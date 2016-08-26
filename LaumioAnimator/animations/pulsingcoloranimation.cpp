#include "pulsingcoloranimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> PulsingColorAnimation::factory() {
    return std::unique_ptr <Animation> (new PulsingColorAnimation());
}

PulsingColorAnimation::PulsingColorAnimation(QObject * parent) : Animation("PulsingColor", parent) {
}

bool PulsingColorAnimation::animationStart(Laumio &laumio) {
    (this->*pulseSignal)(0.0);
    laumio.send_color(color());
    return true;
}

bool PulsingColorAnimation::animationUpdate(Laumio &laumio, double time) {
    (this->*pulseSignal)(time);
    laumio.send_color(color());
    return true;
}

void PulsingColorAnimation::animationStop(Laumio &laumio) {
    (this->*pulseSignal)(duration());
    laumio.send_color(color());
}

void PulsingColorAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("lowerColor") and obj.contains("upperColor")) {
        QColor lowerColor = QColor(obj["lowerColor"].toString());
        QColor upperColor = QColor(obj["upperColor"].toString());
        set_meanColor(QColor((upperColor.red() + lowerColor.red()) / 2, (upperColor.green() + lowerColor.green()) / 2, (upperColor.blue() + lowerColor.blue()) / 2));
        set_varColor(QColor((upperColor.red() - lowerColor.red()) / 2, (upperColor.green() - lowerColor.green()) / 2, (upperColor.blue() - lowerColor.blue()) / 2));
    }
    if (obj.contains("frequency")) set_pulsation(obj["frequency"].toDouble() * 2 * M_PI);
    if (obj.contains("delay")) set_delay(obj["delay"].toDouble());
    if (obj.contains("pulseSignal")) set_pulseSignal(obj["pulseSignal"].toString());
    if (obj.contains("priority")) set_priority(obj["priority"].toInt());
}

void PulsingColorAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    QColor lowerColor(meanColor().red() - varColor().red(), meanColor().green() - varColor().green(), meanColor().blue() - varColor().blue());
    obj["lowerColor"] = lowerColor.name();
    QColor upperColor(meanColor().red() + varColor().red(), meanColor().green() + varColor().green(), meanColor().blue() + varColor().blue());
    obj["upperColor"] = upperColor.name();
    obj["frequency"] = pulsation() / (2 * M_PI);
    obj["delay"] = delay();
    obj["pulseSignal"] = pulseSignalName();
    obj["priority"] = priority();
}


void PulsingColorAnimation::set_pulseSignal(QString name) {
    if (name == "sinus") {
        pulseSignal = &PulsingColorAnimation::sinusSignal;
    } else {
        name = "sinus";
        pulseSignal = &PulsingColorAnimation::sinusSignal;
    }
    m_pulseSignalName = name;
}

void PulsingColorAnimation::sinusSignal(double time) {
    double fac = std::sin(pulsation() * (time - delay()));
    /*
    QColor meanHSV = meanColor().toHsv();
    QColor varHSV = varColor().toHsv();
    int h = meanHSV.hue() + int(fac * varHSV.hue());
    if (h>255) h=255;
    if (h<0) h=0;
    int s = meanHSV.saturation() + int(fac * varHSV.saturation());
    if (s>255) s=255;
    if (s<0) s=0;
    int v = meanHSV.value() + int(fac * varHSV.value());
    if (v>255) v=255;
    if (v<0) v=0;
    m_color.setHsv(h, s, v) ;
    */

    int r = meanColor().red() + int(fac * varColor().red());
    if (r>255) r-=255;
    if (r<0) r+=255;
    int g = meanColor().green() + int(fac * varColor().green());
    if (g>255) g-=255;
    if (g<0) g+=255;
    int b = meanColor().blue() + int(fac * varColor().blue());
    if (b>255) b-=255;
    if (b<0) b+=255;
    m_color.setRgb(r, g, b);

}
