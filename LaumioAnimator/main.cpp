#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "laumio.h"
#include "laumioanimation.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType <Laumio> ("Laumio", 1, 0, "Laumio");
    qmlRegisterType <LaumioAnimation> ("Laumio", 1, 0, "LaumioAnimation");
    qmlRegisterUncreatableType <Animation> ("Laumio", 1, 0, "Animation", "Animation not creatable");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
