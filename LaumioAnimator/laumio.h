#ifndef LAUMIO_H
#define LAUMIO_H

#include <QObject>
#include <QColor>
#include <QUdpSocket>
#include "macrodegeu.h"

/** Object to represent au Laumio with services to communicate with actual hardware **/
class Laumio : public QObject
{
    Q_OBJECT

    /** Property to association a human readable name **/
    PROP(QString, name, "Laumio")

    /** Property to store IP of the laumio's communication interface **/
    PROP(QString, ip, "")

    /** Property to store port of the laumio's communication interface **/
    PROP(int, port, 6969)

    /** Property to store X coordinate ([0..1] percent) **/
    PROP(double, x, 0.5)

    /** Property to store Y coordinate ([0..1] percent) **/
    PROP(double, y, 0.5)

    /** Property to get current color **/
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    /** Constructor
      * @param parent QObject's parent if memory ownership is managed by Qt,
      *               nullptr otherwise
      */
    explicit Laumio(QObject * parent = nullptr);

    /** Load laumio data from JSON
      * @param obj JSON object to load from
      */
    void loadFromJSON(QJsonObject & obj);

    /** Save laumio data in JSON
      * @param obj JSON object to save in
      */
    void saveToJSON(QJsonObject & obj);

public slots:
    /** Get current color
      * @return current color
      */
    QColor color() { return m_color; }

    /** Send color to one led
      * @param led   Led's number
      * @param color Color to send
      */
    void send_color(int led, QColor color);

    /** Send color to whole leds
      * @param color Color to send
      */
    void send_color(QColor color);

    /** Send special animation "rainbow" encoded in laumio **/
    void animRaindow();

    /** Send special animation "colorWipe" encoded in laumio
      * @param color    Base color for the animation
      * @param duration Duration of animation ([0..255] ms)
      */
    void animColorWipe(QColor color = Qt::black, uint8_t duration = 100);

signals:
    /** Signal emitted when color changes **/
    void colorChanged();

private:
    /** Communication socket **/
    static QUdpSocket sock;

    /** Current color **/
    QColor m_color;
};

Q_DECLARE_METATYPE(Laumio*)

#endif // LAUMIO_H
