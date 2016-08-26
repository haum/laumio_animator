#include "mix2colorsanimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> Mix2ColorsAnimation::factory() {
    return std::unique_ptr <Animation> (new Mix2ColorsAnimation());
}

Mix2ColorsAnimation::Mix2ColorsAnimation(QObject * parent) : Animation("Mix2Colors", parent) {
}

bool Mix2ColorsAnimation::animationStart(Laumio &laumio) {
    return animationUpdate(laumio, 0.0);
}

bool Mix2ColorsAnimation::animationUpdate(Laumio &laumio, double time) {
    float sig = Signal::saturate(m_mixSignal->processSignal(time, duration()));

    int r = color1().red() + int(sig * (color2().red() - color1().red()));
    if (r>255) r-=255;
    if (r<0) r+=255;

    int g = color1().green() + int(sig * (color2().green() - color1().green()));
    if (g>255) g-=255;
    if (g<0) g+=255;

    int b = color1().blue() + int(sig * (color2().blue() - color1().blue()));
    if (b>255) b-=255;
    if (b<0) b+=255;

    laumio.send_color(QColor(r, g, b));
    return true;
}

void Mix2ColorsAnimation::animationStop(Laumio &laumio) {
    animationUpdate(laumio, duration());
}

void Mix2ColorsAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("color1")) set_color1(QColor(obj["color1"].toString()));
    if (obj.contains("color2")) set_color2(QColor(obj["color2"].toString()));
    if (obj.contains("mixSignal")) m_mixSignal = std::move(Signal::makeFromJSON(obj["mixSignal"].toObject()));
    if (obj.contains("priority")) set_priority(obj["priority"].toInt());
}

void Mix2ColorsAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    obj["color1"] = color1().name();
    obj["color2"] = color2().name();
    QJsonObject sigobj;
    m_mixSignal->saveToJSON(sigobj);
    obj["mixSignal"] = sigobj;
    obj["priority"] = priority();
}
