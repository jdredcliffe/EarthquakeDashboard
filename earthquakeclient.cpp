#include "earthquakeclient.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

EarthquakeClient::EarthquakeClient(QObject *parent)
    : QObject(parent)
{
}

void EarthquakeClient::fetch(int periodHours, double minMagnitude)
{
    QDateTime startTime = QDateTime::currentDateTimeUtc().addSecs(-periodHours * 3600);

    QUrlQuery query;
    query.addQueryItem("format", "geojson");
    query.addQueryItem("starttime", startTime.toString(Qt::ISODate));
    query.addQueryItem("minmagnitude", QString::number(minMagnitude));
    query.addQueryItem("orderby", "time");
    query.addQueryItem("limit", "200");

    QUrl url("https://earthquake.usgs.gov/fdsnws/event/1/query");
    url.setQuery(query);

    QNetworkReply *reply = m_network.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        handleReply(reply);
    });
}

void EarthquakeClient::handleReply(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        emit requestFailed(reply->errorString());
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    if (!document.isObject() || !document.object().value("features").isArray()) {
        emit requestFailed("Invalid response from the API");
        return;
    }

    QJsonArray features = document.object().value("features").toArray();
    emit earthquakesReceived(parse(features));
}

QList<Earthquake> EarthquakeClient::parse(const QJsonArray &features)
{
    QList<Earthquake> earthquakes;

    for (const QJsonValue &value : features) {
        QJsonObject feature = value.toObject();
        QJsonObject properties = feature.value("properties").toObject();
        QJsonArray coordinates = feature.value("geometry").toObject().value("coordinates").toArray();

        Earthquake earthquake;
        earthquake.place = properties.value("place").toString("Unknown place");
        earthquake.magnitude = properties.value("mag").toDouble();
        earthquake.time = QDateTime::fromMSecsSinceEpoch(properties.value("time").toInteger());
        earthquake.url = properties.value("url").toString();

        if (coordinates.size() >= 3) {
            earthquake.longitude = coordinates.at(0).toDouble();
            earthquake.latitude = coordinates.at(1).toDouble();
            earthquake.depth = coordinates.at(2).toDouble();
        }

        earthquakes.append(earthquake);
    }

    return earthquakes;
}