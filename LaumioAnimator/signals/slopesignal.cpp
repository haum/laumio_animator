#include "slopesignal.h"

std::unique_ptr <Signal> SlopeSignal::factory() {
    return std::unique_ptr <Signal> (new SlopeSignal());
}

float SlopeSignal::processSignal(float currentTime, float totalTime) {
    return from + (to-from) * currentTime/totalTime;
}

void SlopeSignal::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("from")) from = obj["from"].toDouble();
    if (obj.contains("to")) to = obj["to"].toDouble();
}

void SlopeSignal::saveToJSON(QJsonObject & obj) {
    obj["type"] = name();
    obj["from"] = from;
    obj["to"] = to;
}

QString SlopeSignal::name() {
    return "slope";
}
