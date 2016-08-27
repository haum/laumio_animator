#ifndef RAINBOWANIMATION_H
#define RAINBOWANIMATION_H


#include <QObject>
#include <QColor>
#include <memory>
#include "animation.h"

/*

JSON format :

{
    "duration" = <NB>,
    "fromStart" = <NB>
}

*/

/** Animation which set a laumio to a constant color **/
class RainbowAnimation : public Animation
{
    Q_OBJECT

    /** Property storing rectangle color in timeline **/
    PROP(QColor, rectangleColor, "#008888")

public:
    /** Factory function to create the animation
      * @return New animation wrapped in unique_ptr
      */
    static std::unique_ptr <Animation> factory();

    /** Constructor
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit RainbowAnimation(QObject * parent = nullptr);

    virtual bool animationStart(Laumio & laumio) override;
    virtual bool animationUpdate(Laumio & laumio, double time) override;
    virtual void animationStop(Laumio & laumio) override;

    virtual void loadFromJSON(const QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;

private:
    bool done = false;
    double lastCall;
};

#endif // RAINBOWANIMATION_H
