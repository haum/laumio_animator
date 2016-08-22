#include "sumsignal.h"

std::unique_ptr <Signal> SumSignal::factory() {
    return std::unique_ptr <Signal> (new SumSignal());
}

float SumSignal::processSignal(float currentTime, float totalTime) {
    return sig1->processSignal(currentTime, totalTime) + sig2->processSignal(currentTime, totalTime);
}

void SumSignal::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("sig1")) sig1 = Signal::makeFromJSON(obj["sig1"].toObject());
    if (obj.contains("sig2")) sig2 = Signal::makeFromJSON(obj["sig2"].toObject());
}

void SumSignal::saveToJSON(QJsonObject & obj) {
    obj["type"] = name();
    QJsonObject obj1, obj2;
    sig1->saveToJSON(obj1);
    sig2->saveToJSON(obj2);
    obj["sig1"] = obj1;
    obj["sig2"] = obj2;
}

QString SumSignal::name() {
    return "sum";
}
