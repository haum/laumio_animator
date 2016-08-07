#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include "macrodegeu.h"

class Animation : public QObject
{
    Q_OBJECT

    PROP(double, fromStart, 0)
    PROP(double, duration, 0)

public:
    explicit Animation(QString name, QObject *parent = 0);

    virtual void loadFromJSON(QJsonObject & obj) = 0;
    virtual void saveToJSON(QJsonObject & obj) = 0;

public slots:
    QString name();

private:
    QString m_name;
};

#endif // ANIMATION_H
