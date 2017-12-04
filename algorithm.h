
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QImage>
#include <QVector>
#include <QPair>
#include <QPoint>

#include <cmath>

#define DISTOBJ 10. // La distance entre les deux objectifs de la prise stéréoscopique
#define FOCAL   10. // La focale de l'appareil de prise de vue
#define REFMUR  50. // La distance mise en référence sur le mur par les points de repère rouges
#define DISTMUR 200. // La distance (supposée connue) de l'objectif au mur

class InfoConsole;

class Point3D
{
public:

    double distcm;
    double x, y, z;
    Point3D();
    Point3D(double, double, double, double);
};

class Algorithm
{
public:
    Algorithm(InfoConsole*, QImage*, QImage*);

    QVector < Point3D > go();

    QRgb color_of(QImage*, int, int);
    bool is_rep(QImage*, int, int, QRgb);

    QVector < QPoint > find(QImage*, QRgb);
    QPair < QPoint, QPoint > find_norm(QImage*);
    QVector < QPoint > find_refs(QImage*);

    double distance(const QPoint&, const QPoint&);

private:
    InfoConsole* console;
    QImage* imgg;
    QImage* imgd;
};

#endif // ALGORITHM_H
