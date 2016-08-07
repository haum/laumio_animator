#ifndef LAUMIO_H
#define LAUMIO_H

#include <QObject>
#include <QColor>
#include <QUdpSocket>
#include "macrodegeu.h"

class Laumio : public QObject
{
    Q_OBJECT

    PROP(QString, name, "Laumio")
    PROP(QString, ip, "")
    PROP(int, port, 6969)
    PROP(double, x, 0.5)
    PROP(double, y, 0.5)

    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)

public:
    explicit Laumio(QObject * parent = nullptr);

    void loadFromJSON(QJsonObject & obj);
    void saveToJSON(QJsonObject & obj);

public slots:
    QColor color() { return m_color; }
    void send_color(int led, QColor color);
    void animate(QString animation, QColor color);

signals:
    void colorChanged();

private:
    QUdpSocket sock;
    QColor m_color;
};

Q_DECLARE_METATYPE(Laumio*)

#endif // LAUMIO_H
