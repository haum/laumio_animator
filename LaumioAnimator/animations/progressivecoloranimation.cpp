#include "progressivecoloranimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> ProgressiveColorAnimation::factory() {
    return std::unique_ptr <Animation> (new ProgressiveColorAnimation());
}

ProgressiveColorAnimation::ProgressiveColorAnimation(QObject * parent) : Animation("ProgressiveColor", parent) {
}

bool ProgressiveColorAnimation::animationStart(Laumio &laumio) {
    (this->*slopeSignal)(0.0);
    laumio.send_color(color());
    return true;
}

bool ProgressiveColorAnimation::animationUpdate(Laumio &laumio, double time) {
    (this->*slopeSignal)(time);
    laumio.send_color(color());
    return true;
}

void ProgressiveColorAnimation::animationStop(Laumio &laumio) {
    (this->*slopeSignal)(duration());
    laumio.send_color(color());
}

void ProgressiveColorAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("firstColor") and obj.contains("lastColor")) {
        set_firstColor(QColor(obj["firstColor"].toString()));
        set_lastColor(QColor(obj["lastColor"].toString()));
    }
    if (obj.contains("slopeSignal")) set_slopeSignal(obj["slopeSignal"].toString());
    if (obj.contains("priority")) set_priority(obj["priority"].toInt());
}

void ProgressiveColorAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    obj["firstColor"] = firstColor().name();
    obj["lastColor"] = lastColor().name();
    obj["slopeSignal"] = slopeSignalName();
    obj["priority"] = priority();
}


void ProgressiveColorAnimation::set_slopeSignal(QString name) {
    if (name == "linear") {
        slopeSignal = &ProgressiveColorAnimation::linearSignal;
    } else {
        name = "linear";
        slopeSignal = &ProgressiveColorAnimation::linearSignal;
    }
    m_slopeSignalName = name;
}

void ProgressiveColorAnimation::linearSignal(double time) {
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
