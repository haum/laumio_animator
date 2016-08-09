#ifndef CONSTANTCOLORANIMATION_H
#define CONSTANTCOLORANIMATION_H

#include <QObject>
#include <QColor>
#include <memory>
#include "animation.h"
#include "macrodegeu.h"
#include "laumio.h"

class ConstantColorAnimation : public Animation
{
    Q_OBJECT

    PROP(QColor, color, "black")

public:
    static std::unique_ptr <Animation> factory();

    explicit ConstantColorAnimation(QObject * parent = nullptr, Laumio *laumio = nullptr);

    virtual void animate() override;

    virtual void loadFromJSON(QJsonObject & obj) override;
    virtual void saveToJSON(QJsonObject & obj) override;

private:
    bool done = false;
};

#endif // CONSTANTCOLORANIMATION_H
