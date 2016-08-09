#include "animation.h"

Animation::Animation(QString name, QObject *parent, Laumio *laumio) : QObject(parent), m_laumio(laumio), m_name(name) {
}

QString Animation::name() {
    return m_name;
}
