#include "earthquakeclient.h"

#include <QDateTime>
#include <QDebug>
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

    QByteArray data = reply->readAll();
    qDebug() << "Received" << data.size() << "bytes from USGS";

    emit earthquakesReceived(QList<Earthquake>());
}