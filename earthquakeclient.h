#pragma once

#include <QJsonArray>
#include <QList>
#include <QNetworkAccessManager>
#include <QObject>

#include "earthquake.h"

class QNetworkReply;

class EarthquakeClient : public QObject
{
    Q_OBJECT

public:
    explicit EarthquakeClient(QObject *parent = nullptr);

    void fetch(int periodHours, double minMagnitude);

signals:
    void earthquakesReceived(const QList<Earthquake> &earthquakes);
    void requestFailed(const QString &message);

private:
    void handleReply(QNetworkReply *reply);
    QList<Earthquake> parse(const QJsonArray &features);

    QNetworkAccessManager m_network;
};