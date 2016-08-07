#include "animation.h"

Animation::Animation(QString name, QObject *parent) : QObject(parent), m_name(name) {
}

QString Animation::name() {
    return m_name;
}
