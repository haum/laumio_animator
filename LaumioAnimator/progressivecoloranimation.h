#ifndef PROGRESSIVECOLORANIMATION_H
#define PROGRESSIVECOLORANIMATION_H

#include <QObject>
#include <QColor>
#include <memory>
#include <cmath>
#include "animation.h"
#include "macrodegeu.h"
#include "laumio.h"

/** Animation which set a laumio to a progressive color **/
class ProgressiveColorAnimation : public Animation
{
    Q_OBJECT

    /** Property storing color to set **/
    PROP(QColor, color, "black")

    /** Property storing first color parameter **/
    SimplerPROP(QColor, firstColor, QColor(0x00,0x00,0x00))

    /** Property storing last color parameter **/
    SimplerPROP(QColor, lastColor, QColor(0xff,0xff,0xff))

public:
    /** Factory function to create the animation
      * @return New animation wrapped in unique_ptr
      */
    static std::unique_ptr <Animation> factory();

    /** Constructor
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit ProgressiveColorAnimation(QObject * parent = nullptr);

    virtual bool animationStart(Laumio & laumio) override;
    virtual bool animationUpdate(Laumio & laumio, double time) override;
    virtual void animationStop(Laumio & laumio) override;

    virtual void loadFromJSON(const QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;

    QString signalName() { return m_signalName ; }
    void set_signal(QString name);

private:
    bool done = false;

    QString m_signalName = "sinus";
    void (ProgressiveColorAnimation::*slope_signal)(double time) = &ProgressiveColorAnimation::linear_signal;
    void linear_signal(double time);
};



#endif // PROGRESSIVECOLORANIMATION_H
