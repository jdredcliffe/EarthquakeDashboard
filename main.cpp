#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "earthquakeclient.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle(QStringLiteral("Basic"));

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("latestPlace", "Loading...");
    context->setContextProperty("latestMagnitude", "");
    context->setContextProperty("latestTime", "");

    EarthquakeClient client;
    QObject::connect(&client, &EarthquakeClient::requestFailed, [context](const QString &message) {
        context->setContextProperty("latestPlace", "Error: " + message);
    });
    QObject::connect(&client, &EarthquakeClient::earthquakesReceived, [context](const QList<Earthquake> &earthquakes) {
        if (earthquakes.isEmpty()) {
            context->setContextProperty("latestPlace", "No earthquakes found");
            return;
        }
        Earthquake latest = earthquakes.first();
        context->setContextProperty("latestPlace", latest.place);
        context->setContextProperty("latestMagnitude", QString::number(latest.magnitude, 'f', 1));
        context->setContextProperty("latestTime", latest.time.toString("HH:mm:ss dd/MM/yy"));
    });
    client.fetch(24, 2.5);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("EarthquakeDashboard", "Main");

    return QGuiApplication::exec();
}