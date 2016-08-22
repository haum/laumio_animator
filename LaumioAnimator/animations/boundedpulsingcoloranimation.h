#ifndef BOUNDEDPULSINGCOLORANIMATION_H
#define BOUNDEDPULSINGCOLORANIMATION_H

#include <QObject>
#include <QColor>
#include <memory>
#include <cmath>
#include "animation.h"

/*

JSON format :

{
    "delay" = <NB>,
    "duration" = <NB>,
    "firstLowerColor" = "<COLOR>",
    "firstUpperColor" = "<COLOR>",
    "frequency" = <NB>,
    "fromStart" = <NB>,
    "lastLowerColor" = "<COLOR>",
    "lastUpperColor" = "<COLOR>",
    "lowerSignal" = "<SIGNAL>",
    "pulseSignal" = "<SIGNAL>",
    "upperSignal" = "<SIGNAL>"
}

*/

class BoundedPulsingColorAnimation : public Animation
{
    Q_OBJECT

    /** Property storing rectangle color in timeline **/
    PROP(QColor, rectangleColor, "#008800")

    /** Property storing color to set **/
    PROP(QColor, color, "black")

    /** Property storing first lower color parameter **/
    PROP(QColor, firstLowerColor, QColor(0x00,0x00,0x00))

    /** Property storing last lower color parameter **/
    PROP(QColor, lastLowerColor, QColor(0xff,0xff,0xff))

    /** Property storing first upper color parameter **/
    PROP(QColor, firstUpperColor, QColor(0x00,0x00,0x00))

    /** Property storing last upper color parameter **/
    PROP(QColor, lastUpperColor, QColor(0xff,0xff,0xff))

    /** Property storing pulsation signal, in rad/s **/
    PROP(double, pulsation, 2 * M_PI)

    /** Property storing phase-delay signal from start, in seconds **/
    PROP(double, delay, 0.0)

public:
    /** Factory function to create the animation
      * @return New animation wrapped in unique_ptr
      */
    static std::unique_ptr <Animation> factory();

    /** Constructor
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit BoundedPulsingColorAnimation(QObject * parent = nullptr);

    virtual bool animationStart(Laumio & laumio) override;
    virtual bool animationUpdate(Laumio & laumio, double time) override;
    virtual void animationStop(Laumio & laumio) override;

    virtual void loadFromJSON(const QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;

    QString upperBoundSignalName() { return m_upperBoundSignalName ; }
    void set_upperBoundSignal(QString name);

    QString lowerBoundSignalName() { return m_lowerBoundSignalName ; }
    void set_lowerBoundSignal(QString name);

    QString pulseSignalName() { return m_pulseSignalName ; }
    void set_pulseSignal(QString name);

private:
    bool done = false;

    void computeColor(double time) ;

    QString m_upperBoundSignalName = "linear";
    QString m_lowerBoundSignalName = "linear";
    QString m_pulseSignalName = "sinus";

    double (BoundedPulsingColorAnimation::*upperBoundSlopeSignal)(double time) = &BoundedPulsingColorAnimation::linearSignal;
    double (BoundedPulsingColorAnimation::*lowerBoundSlopeSignal)(double time) = &BoundedPulsingColorAnimation::linearSignal;
    double (BoundedPulsingColorAnimation::*pulseSignal)(double time) = &BoundedPulsingColorAnimation::sinusSignal;

    double linearSignal(double time);
    double sinusSignal(double time);

};

#endif // BOUNDEDPULSINGCOLORANIMATION_H
