#include "constantcoloranimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> ConstantColorAnimation::factory() {
    return std::unique_ptr <Animation> (new ConstantColorAnimation());
}

ConstantColorAnimation::ConstantColorAnimation(QObject * parent) : Animation("ConstantColor", parent) {
}

bool ConstantColorAnimation::animationStart(Laumio &laumio) {
    laumio.send_color(color());
    return false;
}

void ConstantColorAnimation::animationStop(Laumio &laumio) {
    laumio.send_color(color());
}

void ConstantColorAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("color")) set_color(QColor(obj["color"].toString()));
    if (obj.contains("priority")) set_priority(obj["priority"].toInt());
}

void ConstantColorAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    obj["color"] = color().name();
    obj["priority"] = priority();
}
