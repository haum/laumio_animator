#include "laumio.h"
#include <QJsonObject>

Laumio::Laumio(QObject * parent) : QObject(parent) {
}

void Laumio::loadFromJSON(QJsonObject & obj) {
    if (obj.contains("name")) set_name(obj["name"].toString());
    if (obj.contains("ip")) set_ip(obj["ip"].toString());
    if (obj.contains("port")) set_port(obj["port"].toInt());
    if (obj.contains("x")) set_x(obj["x"].toDouble());
    if (obj.contains("y")) set_y(obj["y"].toDouble());
}

void Laumio::saveToJSON(QJsonObject & obj) {
    obj["name"] = name();
    obj["ip"] = ip();
    obj["port"] = port();
    obj["x"] = x();
    obj["y"] = y();
}

void Laumio::send_color(int led, QColor color) {
    char data[5];
    int len = 0;
    if (led != 255) {
        data[0] = 0;
        data[1] = led;
        data[2] = color.red();
        data[3] = color.green();
        data[4] = color.blue();
        len = 5;
    } else {
        data[0] = led;
        data[1] = color.red();
        data[2] = color.green();
        data[3] = color.blue();
        len = 4;
    }
    m_color = color;
    emit colorChanged();
    sock.writeDatagram(data, len, QHostAddress(m_ip), m_port);
}

void Laumio::animate(QString animation = "default", QColor color = "black") {
    char data[5];
    int len = 0;
    if (animation == "rainbow") {
        data[0] = 10;
        len = 1;
    } else if (animation == "colorWipe") {
        data[0] = 11;
        data[1] = color.red();
        data[2] = color.green();
        data[3] = color.blue();
        len = 4;
    }
    sock.writeDatagram(data, len, QHostAddress(m_ip), m_port);
}
