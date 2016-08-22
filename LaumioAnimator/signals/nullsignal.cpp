#include "nullsignal.h"

std::unique_ptr <Signal> NullSignal::factory() {
    return std::unique_ptr <Signal> (new NullSignal());
}

float NullSignal::processSignal(float currentTime, float totalTime) {
    Q_UNUSED(currentTime)
    Q_UNUSED(totalTime)
    return 0;
}

void NullSignal::loadFromJSON(const QJsonObject & obj) {
    Q_UNUSED(obj)
    // Nothing to load
}

void NullSignal::saveToJSON(QJsonObject & obj) {
    obj["type"] = name();
}

QString NullSignal::name() {
    return "null";
}
