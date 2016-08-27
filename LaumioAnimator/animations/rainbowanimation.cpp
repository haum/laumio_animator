#include "rainbowanimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> RainbowAnimation::factory() {
    return std::unique_ptr <Animation> (new RainbowAnimation());
}

RainbowAnimation::RainbowAnimation(QObject * parent) : Animation("Rainbow", parent) {
}

bool RainbowAnimation::animationStart(Laumio &laumio) {
    laumio.animRainbow();
    lastCall = 0;
    return true;
}

bool RainbowAnimation::animationUpdate(Laumio &laumio, double time) {
    if(time - lastCall >= 1.8){
        laumio.animRainbow();
        lastCall = time;
    }
    return true;
}

void RainbowAnimation::animationStop(Laumio &laumio) {
}

void RainbowAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("priority")) set_priority(obj["priority"].toInt());
}

void RainbowAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    obj["priority"] = priority();
}
