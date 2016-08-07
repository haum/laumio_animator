#include "constantcoloranimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> ConstantColorAnimation::factory() {
    return std::unique_ptr <Animation> (new ConstantColorAnimation());
}

ConstantColorAnimation::ConstantColorAnimation(QObject * parent) : Animation("ConstantColor", parent) {
}

void ConstantColorAnimation::loadFromJSON(QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("color")) set_color(QColor(obj["color"].toString()));
}

void ConstantColorAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    obj["color"] = color().name();
}
