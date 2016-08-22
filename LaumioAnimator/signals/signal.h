#ifndef SIGNAL_H
#define SIGNAL_H

#include <QJsonObject>
#include <memory>
#include <map>

/** Base class for signal **/
class Signal
{
public:
    /** Process signal
      * @param currentTime Time at which to compute signal
      * @param totalTime   Total time of signal
      * @param saturate    Should signal be saturated to be in [0..1]
      * @return Signal value (1.0 is 100%)
      */
    virtual float processSignal(float currentTime, float totalTime) = 0;

    /** Load signal from JSON
      * @param obj JSON object to load from
      */
    virtual void loadFromJSON(const QJsonObject & obj) = 0;

    /** Save signal in JSON
      * @param obj JSON object to save in
      */
    virtual void saveToJSON(QJsonObject & obj) = 0;

    /** Get signal name
      * @return Signal name
      */
    virtual QString name() = 0;

    /** Make Signal object from JSON
      * @param obj JSON object to load from
      * @return New signal object
      */
    static std::unique_ptr <Signal> makeFromJSON(const QJsonObject & obj);

    /** Saturate signal in [0..1]
      * @param value Value to saturate
      * @return Saturated value
      */
    static float saturate(float value) {
        return value > 1 ? 1 : value < 0 ? 0 : value;
    }

private:
    /** Factories **/
    static std::map <QString, std::unique_ptr <Signal> (*)()> sFactories;
};

#endif // ANIMATION_H
