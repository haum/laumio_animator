#ifndef MIX2COLORSANIMATION_H
#define MIX2COLORSANIMATION_H

#include "../signals/signal.h"
#include "animation.h"

/*

JSON format :

{
    "color1" = "<COLOR>",
    "color2" = "<COLOR>",
    "duration" = <NB>,
    "fromStart" = <NB>,
    "mixSignal" = <SIGNAL>
}

*/

/** Animation which mixes two color based on a signal **/
class Mix2ColorsAnimation : public Animation
{
    Q_OBJECT

    /** Property storing first color **/
    PROP(QColor, color1, "black")

    /** Property storing second color **/
    PROP(QColor, color2, "white")

public:
    /** Factory function to create the animation
      * @return New animation wrapped in unique_ptr
      */
    static std::unique_ptr <Animation> factory();

    /** Constructor
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit Mix2ColorsAnimation(QObject * parent = nullptr);

    virtual bool animationStart(Laumio & laumio) override;
    virtual bool animationUpdate(Laumio & laumio, double time) override;
    virtual void animationStop(Laumio & laumio) override;

    virtual void loadFromJSON(const QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;

private:
    std::unique_ptr <Signal> m_mixSignal;
};

#endif // MIX2COLORSANIMATION_H
