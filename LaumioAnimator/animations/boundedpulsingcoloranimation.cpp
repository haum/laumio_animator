#include "boundedpulsingcoloranimation.h"
#include <QJsonObject>

std::unique_ptr <Animation> BoundedPulsingColorAnimation::factory() {
    return std::unique_ptr <Animation> (new BoundedPulsingColorAnimation());
}

BoundedPulsingColorAnimation::BoundedPulsingColorAnimation(QObject * parent) : Animation("BoundedPulsingColor", parent) {
}

bool BoundedPulsingColorAnimation::animationStart(Laumio &laumio) {
    computeColor(0.0);
    laumio.send_color(color());
    return true;
}

bool BoundedPulsingColorAnimation::animationUpdate(Laumio &laumio, double time) {
    computeColor(time);
    laumio.send_color(color());
    return true;
}

void BoundedPulsingColorAnimation::animationStop(Laumio &laumio) {
    computeColor(duration());
    laumio.send_color(color());
}

#include <QDebug>
void BoundedPulsingColorAnimation::loadFromJSON(const QJsonObject & obj) {
    if (obj.contains("fromStart")) set_fromStart(obj["fromStart"].toDouble());
    if (obj.contains("duration")) set_duration(obj["duration"].toDouble());
    if (obj.contains("firstLowerColor")) set_firstLowerColor(QColor(obj["firstLowerColor"].toString()));
    if (obj.contains("lastLowerColor")) set_lastLowerColor(QColor(obj["lastLowerColor"].toString()));
    if (obj.contains("firstUpperColor")) set_firstUpperColor(QColor(obj["firstUpperColor"].toString()));
    if (obj.contains("lastUpperColor")) set_lastUpperColor(QColor(obj["lastUpperColor"].toString()));
    if (obj.contains("pulseSignal")) set_pulseSignal(obj["pulseSignal"].toString());
    if (obj.contains("upperSignal")) set_upperBoundSignal(obj["upperSignal"].toString());
    if (obj.contains("lowerSignal")) set_lowerBoundSignal(obj["lowerSignal"].toString());
    if (obj.contains("frequency")) set_pulsation(obj["frequency"].toDouble() * 2 * M_PI);
    if (obj.contains("delay")) set_delay(obj["delay"].toDouble());
    qDebug() << fromStart() << duration() << firstLowerColor().name() << lastLowerColor().name() << firstUpperColor().name()  << lastUpperColor().name() << upperBoundSignalName() << lowerBoundSignalName() << pulseSignalName() << pulsation() << delay();

}

void BoundedPulsingColorAnimation::saveToJSON(QJsonObject & obj) {
    obj["fromStart"] = fromStart();
    obj["duration"] = duration();
    obj["firstLowerColor"] = firstLowerColor().name();
    obj["lastLowerColor"] = lastLowerColor().name();
    obj["firstUpperColor"] = firstUpperColor().name();
    obj["lastUpperColor"] = lastUpperColor().name();
    obj["pulseSignal"] = pulseSignalName();
    obj["upperSignal"] = upperBoundSignalName();
    obj["lowerSignal"] = lowerBoundSignalName();
    obj["frequency"] = pulsation() / (2 * M_PI);
    obj["delay"] = delay();
}


void BoundedPulsingColorAnimation::set_upperBoundSignal(QString name) {
    if (name == "linear") {
        upperBoundSlopeSignal = &BoundedPulsingColorAnimation::linearSignal;
    } else {
        name = "linear";
        upperBoundSlopeSignal = &BoundedPulsingColorAnimation::linearSignal;
    }
    m_upperBoundSignalName = name;
}

void BoundedPulsingColorAnimation::set_lowerBoundSignal(QString name) {
    if (name == "linear") {
        lowerBoundSlopeSignal = &BoundedPulsingColorAnimation::linearSignal;
    } else {
        name = "linear";
        lowerBoundSlopeSignal = &BoundedPulsingColorAnimation::linearSignal;
    }
    m_lowerBoundSignalName = name;
}

void BoundedPulsingColorAnimation::set_pulseSignal(QString name) {
    if (name == "sinus") {
        pulseSignal = &BoundedPulsingColorAnimation::sinusSignal;
    } else {
        name = "sinus";
        pulseSignal = &BoundedPulsingColorAnimation::sinusSignal;
    }
    m_pulseSignalName = name;
}
//#include <QDebug>
void BoundedPulsingColorAnimation::computeColor(double time) {
    double upperVal = (this->*upperBoundSlopeSignal)(time);
    double lowerVal = (this->*lowerBoundSlopeSignal)(time);
    double pulseVal = (this->*pulseSignal)(time);
//qDebug() << time << upperVal << pulseVal << lowerVal;

    QColor upperColor = QColor(firstUpperColor().red() + int(upperVal * (lastUpperColor().red() - firstUpperColor().red())), firstUpperColor().green() + int(upperVal * (lastUpperColor().green() - firstUpperColor().green())), firstUpperColor().blue() + int(upperVal * (lastUpperColor().blue() - firstUpperColor().blue())));
    QColor lowerColor = QColor(firstLowerColor().red() + int(lowerVal * (lastLowerColor().red() - firstLowerColor().red())), firstLowerColor().green() + int(lowerVal * (lastLowerColor().green() - firstLowerColor().green())), firstLowerColor().blue() + int(lowerVal * (lastLowerColor().blue() - firstLowerColor().blue())));
//qDebug() << upperColor.name() << lowerColor.name();

    QColor meanColor = QColor((upperColor.red() + lowerColor.red()) / 2, (upperColor.green() + lowerColor.green()) / 2, (upperColor.blue() + lowerColor.blue()) / 2);
    QColor varColor = QColor((upperColor.red() - lowerColor.red()) / 2, (upperColor.green() - lowerColor.green()) / 2, (upperColor.blue() - lowerColor.blue()) / 2);
//qDebug() << meanColor.name() << varColor.name();

    m_color = QColor(meanColor.red() + int(pulseVal * varColor.red()), meanColor.green() + int(pulseVal * varColor.green()), meanColor.blue() + int(pulseVal * varColor.blue()));
}

double BoundedPulsingColorAnimation::sinusSignal(double time) {
    return std::sin(pulsation() * (time - delay()));
}

double BoundedPulsingColorAnimation::linearSignal(double time) {
    return time / duration();
}

