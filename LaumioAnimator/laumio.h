#ifndef LAUMIO_H
#define LAUMIO_H

#include <QObject>
#include <QColor>
#include <QUdpSocket>

/** Ugly macro to simplify definition of trivial properties **/
#define PROP(TYPE, NAME, DEFAULT) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE set_##NAME NOTIFY NAME##Changed) \
    public slots: \
        void set_##NAME(TYPE NAME) { \
            if (m_##NAME != NAME) { \
                m_##NAME = NAME; \
                emit NAME##Changed(); \
            } \
        } \
        TYPE NAME() { \
            return m_##NAME;\
        } \
    Q_SIGNAL \
        void NAME##Changed(); \
    private: \
        TYPE m_##NAME {DEFAULT};

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
