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
    (this->*slope_signal)(duration());
    laumio.send_color(color());
}

void ProgressiveColorAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("first_color") and obj.contains("last_color")) {
        set_firstColor(QColor(obj["first_color"].toString()));
        set_lastColor(QColor(obj["last_color"].toString()));
    }
    if (obj.contains("signal")) set_signal(obj["signal"].toString());
}

void ProgressiveColorAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    obj["first_color"] = firstColor().name();
    obj["last_color"] = lastColor().name();
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
    double fac = time / duration();

    /*
    QColor firstHSV = firstColor().toHsv();
    QColor lastHSV = lastColor().toHsv();
    int h = firstHSV.hue() + int(fac * (lastHSV.hue() - firstHSV.hue()));
    if (h>255) h-=255;
    if (h<0) h+=255;
    int s = firstHSV.saturation() + int(fac * (lastHSV.saturation() - firstHSV.saturation()));
    if (s>255) s-=255;
    if (s<0) s+=255;
    int v = firstHSV.value() + int(fac * (lastHSV.value() - firstHSV.value()));
    if (v>255) v-=255;
    if (v<0) v+=255;
    m_color.setHsv(h, s, v) ;
    */

    int r = firstColor().red() + int(fac * (lastColor().red() - firstColor().red()));
    if (r>255) r-=255;
    if (r<0) r+=255;
    int g = firstColor().green() + int(fac * (lastColor().green() - firstColor().green()));
    if (g>255) g-=255;
    if (g<0) g+=255;
    int b = firstColor().blue() + int(fac * (lastColor().blue() - firstColor().blue()));
    if (b>255) b-=255;
    if (b<0) b+=255;
    m_color.setRgb(r, g, b);
}
