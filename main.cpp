#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "earthquakeclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle(QStringLiteral("Basic"));

    EarthquakeClient client;
    QObject::connect(&client, &EarthquakeClient::requestFailed, [](const QString &message) {
        qDebug() << "Request failed:" << message;
    });
    client.fetch(24, 2.5);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("EarthquakeDashboard", "Main");

    return QGuiApplication::exec();
}