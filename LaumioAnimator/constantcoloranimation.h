#ifndef CONSTANTCOLORANIMATION_H
#define CONSTANTCOLORANIMATION_H

#include <QObject>
#include <QColor>
#include <memory>
#include "animation.h"
#include "macrodegeu.h"

class ConstantColorAnimation : public Animation
{
    Q_OBJECT

    PROP(QColor, color, "black")

public:
    static std::unique_ptr <Animation> factory();

    explicit ConstantColorAnimation(QObject * parent = nullptr);    

    virtual void loadFromJSON(QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;
};

#endif // CONSTANTCOLORANIMATION_H
