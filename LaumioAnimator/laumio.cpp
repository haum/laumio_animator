#include "laumio.h"
#include <QJsonObject>

QUdpSocket Laumio::sock;

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
    data[0] = 0;
    data[1] = led;
    data[2] = color.red();
    data[3] = color.green();
    data[4] = color.blue();
    sock.writeDatagram(data, sizeof(data), QHostAddress(m_ip), m_port);
}

void Laumio::send_color(QColor color) {
    char data[4];
    data[0] = 0xff;
    data[1] = color.red();
    data[2] = color.green();
    data[3] = color.blue();
    m_color = color;
    emit colorChanged();
    sock.writeDatagram(data, sizeof(data), QHostAddress(m_ip), m_port);
}

void Laumio::animRaindow() {
    char data[1];
    data[0] = 10;
    sock.writeDatagram(data, sizeof(data), QHostAddress(m_ip), m_port);
}

void Laumio::animColorWipe(QColor color, uint8_t duration) {
    char data[5];
    data[0] = 11;
    data[1] = color.red();
    data[2] = color.green();
    data[3] = color.blue();
    data[4] = duration;
    sock.writeDatagram(data, sizeof(data), QHostAddress(m_ip), m_port);
}
