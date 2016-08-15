#ifndef PULSINGCOLORANIMATION_H
#define PULSINGCOLORANIMATION_H

#include <QObject>
#include <QColor>
#include <memory>
#include <cmath>
#include "animation.h"
#include "macrodegeu.h"
#include "laumio.h"

/** Animation which set a laumio to a pulsing color **/
class PulsingColorAnimation : public Animation
{
    Q_OBJECT

    /** Property storing color to set **/
    PROP(QColor, color, "black")

    /** Property storing mean color parameter **/
    SimplerPROP(QRgb, meanColor, qRgb(0,0,0))

    /** Property storing amplitude parameter of color variation **/
    SimplerPROP(QRgb, varColor, qRgb(0,0,0))

    /** Property storing pulsation signal **/
    SimplerPROP(double, pulsation, 0.0)

    /** Property storing phase-delay signal from start **/
    SimplerPROP(double, delay, 0.0)

public:
    /** Factory function to create the animation
      * @return New animation wrapped in unique_ptr
      */
    static std::unique_ptr <Animation> factory();

    /** Constructor
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit PulsingColorAnimation(QObject * parent = nullptr);

    virtual bool animationStart(Laumio & laumio) override;
    virtual bool animationUpdate(Laumio & laumio, double time) override;
    virtual void animationStop(Laumio & laumio) override;

    virtual void loadFromJSON(const QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;

    void set_signal(QString name);

private:
    bool done = false;

    void (PulsingColorAnimation::*pulse_signal)(double time);
    void sinus_signal(double time);
};



#endif // PULSINGCOLORANIMATION_H
