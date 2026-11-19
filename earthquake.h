#pragma once

#include <QDateTime>
#include <QString>

struct Earthquake
{
    QString place;
    double magnitude = 0.0;
    QDateTime time;
    double depth = 0.0;
    double latitude = 0.0;
    double longitude = 0.0;
    QString url;
};