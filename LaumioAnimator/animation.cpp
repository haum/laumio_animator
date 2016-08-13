#include "animation.h"

Animation::Animation(const QString name, QObject *parent) : QObject(parent), m_name(name) {
}

QString Animation::name() {
    return m_name;
}

bool Animation::animationStart(Laumio &laumio) {
    Q_UNUSED(laumio)
    return true;
}

bool Animation::animationUpdate(Laumio &laumio, double time) {
    Q_UNUSED(laumio)
    Q_UNUSED(time)
    return false;
}

void Animation::animationStop(Laumio &laumio) {
    Q_UNUSED(laumio)
}
