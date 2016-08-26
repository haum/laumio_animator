#ifndef CONSTANTCOLORANIMATION_H
#define CONSTANTCOLORANIMATION_H

#include <QObject>
#include <QColor>
#include <memory>
#include "animation.h"

/*

JSON format :

{
    "color" = "<COLOR>",
    "duration" = <NB>,
    "fromStart" = <NB>
}

*/

/** Animation which set a laumio to a constant color **/
class ConstantColorAnimation : public Animation
{
    Q_OBJECT

    /** Property storing rectangle color in timeline **/
    PROP(QColor, rectangleColor, "#ff0000")

    /** Property storing color to set **/
    PROP(QColor, color, "black")

public:
    /** Factory function to create the animation
      * @return New animation wrapped in unique_ptr
      */
    static std::unique_ptr <Animation> factory();

    /** Constructor
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit ConstantColorAnimation(QObject * parent = nullptr);

    virtual bool animationStart(Laumio & laumio) override;
    virtual bool animationUpdate(Laumio & laumio, double time) override;
    virtual void animationStop(Laumio & laumio) override;

    virtual void loadFromJSON(const QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;

private:
    bool done = false;
};

#endif // CONSTANTCOLORANIMATION_H
