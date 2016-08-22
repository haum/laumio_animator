#include "signal.h"

#include "nullsignal.h"
#include "slopesignal.h"
#include "sumsignal.h"

std::map <QString, std::unique_ptr <Signal> (*)()> Signal::sFactories {
    {"null", &NullSignal::factory},
    {"slope", &SlopeSignal::factory},
    {"sum", &SumSignal::factory},
};

std::unique_ptr <Signal> Signal::makeFromJSON(const QJsonObject & obj) {
    QString factoryName = obj["type"].toString();
    auto itFactory = sFactories.find(factoryName);
    if (itFactory != std::end(sFactories)) {
        auto sig = (*itFactory->second)();
        sig->loadFromJSON(obj);
        return sig;
    }
    return std::unique_ptr <Signal> (new NullSignal);
}
