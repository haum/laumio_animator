#ifndef SUMSIGNAL_H
#define SUMSIGNAL_H

#include "signal.h"

/*

JSON format :

{
    "sig1": <SIGNAL>,
    "sig2": <SIGNAL>,
    "type" = "sum"
}

*/

/** Signal that sums to other signals **/
class SumSignal : public Signal
{
public:
    /** Factory function to create the signal
      * @return New signal wrapped in unique_ptr
      */
    static std::unique_ptr <Signal> factory();

    virtual float processSignal(float currentTime, float totalTime) override;
    virtual void loadFromJSON(const QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;
    virtual QString name() override;

private:
    std::unique_ptr <Signal> sig1;
    std::unique_ptr <Signal> sig2;
};

#endif // SUMSIGNAL_H
