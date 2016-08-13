#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include "macrodegeu.h"
#include "laumio.h"

/** Base class for animations **/
class Animation : public QObject
{
    Q_OBJECT

    /** Property to store start time from beggining of sequence (in seconds) **/
    PROP(double, fromStart, 0)

    /** Property to store duration of the animation (in seconds) **/
    PROP(double, duration, 0)

    /** Property to get animation's code name **/
    Q_PROPERTY(QString name READ name CONSTANT)

public:
    /** Constructor
      * @param name   Animation code name
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit Animation(const QString name, QObject * parent = nullptr);

    /** Function called when animation starts
      * @param laumio Laumio to light
      * @return true if engine should call animationUpdate, false otherwise
      */
    virtual bool animationStart(Laumio & laumio);

    /** Function called at regular when animation is run
      * @param laumio Laumio to light
      * @param time   Time from start of animation in seconds
      * @return true if engine should continue to call animationUpdate, false otherwise
      */
    virtual bool animationUpdate(Laumio & laumio, double time);

    /** Function called when animation stops
      * @param laumio Laumio to light
      */
    virtual void animationStop(Laumio & laumio);

    /** Load animation from JSON
      * @param obj JSON object to load from
      */
    virtual void loadFromJSON(const QJsonObject & obj) = 0;

    /** Save animation in JSON
      * @param obj JSON object to save in
      */
    virtual void saveToJSON(QJsonObject & obj) = 0;

public slots:
    /** Get animation's code name **/
    QString name();

private:
    /** Animation's code name **/
    QString m_name;
};

#endif // ANIMATION_H
