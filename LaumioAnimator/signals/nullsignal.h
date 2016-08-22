#ifndef NULLSIGNAL_H
#define NULLSIGNAL_H

#include "signal.h"

/*

JSON format :

{
    "type": "null"
}

*/

/** Signal always 0 **/
class NullSignal : public Signal
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
};

#endif // NULLSIGNAL_H
