#ifndef SLOPESIGNAL_H
#define SLOPESIGNAL_H

#include "signal.h"

/*

JSON format :

{
    "from": <NB>,
    "to": <NB>,
    "type" = "slope"
}

*/

/** Signal that makes a slope **/
class SlopeSignal : public Signal
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
    float from {0};
    float to {1};
};

#endif // SLOPESIGNAL_H
