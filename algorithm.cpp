
#include "algorithm.h"
#include "infoconsole.h"

Point3D::Point3D()
    : distcm(0.), x(0.), y(0.), z(0.)
{
}

Point3D::Point3D(double dcm, double x_, double y_, double z_)
    : distcm(dcm), x(x_), y(y_), z(z_)
{
}

Algorithm::Algorithm(InfoConsole* c, QImage* g, QImage* d)
    : console(c), imgg(g), imgd(d)
{
}

QRgb Algorithm::color_of(QImage* img, int x, int y)
{
    uint* rgb = (uint*)img->scanLine(y) + x;
    return qRgb(qRed(*rgb), qGreen(*rgb), qBlue(*rgb));

    //int r = qRed(*rgb), g = qGreen(*rgb), b = qBlue(*rgb);
    //return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

bool Algorithm::is_rep(QImage* img, int x, int y, QRgb color)
{
    bool check1 = color_of(img, x-1, y) != color
               && color_of(img, x, y-1) != color
       , check2 = true;

    for(int i = 0; i != 4; ++i)
        for(int j = 0; j != 4; ++j)
            if(color_of(img, x + i, y + j) != color)
            {
                check2 = false;
                break;
            }

    return check1 && check2;
}

QVector < QPoint > Algorithm::find(QImage* img, QRgb color)
{
    // Ici, on trouve les repères (petits carrés d'une couleur précise spécifiée en paramètre)
    // sur l'image passé en paramètre, on les symbolise par des points 2D, indexés par les pixels
    // et on les renvoie sous forme de tableau
    QVector < QPoint > res;

    for(int x = 1; x != img->width() - 4; ++x)
        for(int y = 1; y != img->height() - 4; ++y)
            if(color_of(img, x, y) == color && is_rep(img, x, y, color))
                res.push_back(QPoint(x, y));

    return res;
}

QPair < QPoint, QPoint > Algorithm::find_norm(QImage* img)
{
    // Spécialisation de find(), ici on trouve les repères de normes (couleur rouge)
    // (Note : il doit y en avoir deux exactement)

    QVector < QPoint > norms = this->find(img, qRgb(255, 0, 0));

    if(norms.size() != 2)
    {
        console->write_error("il doit y avoir exactement deux points de normes");
        console->write_error_compl("Reperes de couleur RGB(255, 0, 0)");
        throw std::exception();
    }

    return qMakePair(norms[0], norms[1]);
}

QVector < QPoint > Algorithm::find_refs(QImage* img)
{
    // Spécialisation de find(), ici on trouve les repères de références (couleur verte)
    return this->find(img, qRgb(0, 255, 0));
}

double Algorithm::distance(const QPoint& a, const QPoint& b)
{
    return std::sqrt(std::pow((double)(a.x() - b.x()), 2.) + std::pow((double)(a.y() - b.y()), 2.));
}

QVector < Point3D > Algorithm::go()
{
    // ALGORITHME PRINCIPAL
    // ......
    // C'est ici que l'on crée quelque chose d'affichable par OpenGL à partir
    // des deux images d'entrées

    QVector < Point3D > points;

    // On commence par récupérer une norme (à partir de l'image gauche ou droite,
    // peu importe, la norme est la même)
    QPair < QPoint, QPoint > norm = this->find_norm(imgg);
    QPair < QPoint, QPoint > dnorm = this->find_norm(imgd);
    double distpixnorm = distance(norm.first, norm.second);

    // On récupère les points de références pour les deux images
    // (Il s'agira ensuite d'en faire la correspondance)
    QVector < QPoint >
        grefs = this->find_refs(imgg)
      , drefs = this->find_refs(imgd);

    if(grefs.size() != drefs.size())
    {
        console->write_error("il doit y avoir le même nombre de points de repère sur les deux images");
        console->write_error_compl(QString::number(grefs.size()) + " à gauche contre " + QString::number(drefs.size()) + " à droite");
        throw std::exception();
    }

    int rsize = grefs.size(); // == drefs.size()

    // Maintenant on peut facilement établir les correspondances entre grefs et drefs :
    // En effet, vu que la caméra n'a effectué qu'un déplacement de translation horizontale,
    // les points de repère apparaissent dans le même ordre, que l'on balaye l'image gauche
    // ou l'image droite. On peut donc faire une correspondance en miroir entre les deux tableaux !

    double mopening = REFMUR * (distance(norm.first, dnorm.first)) / distpixnorm;
    double mdist = DISTOBJ * FOCAL / (mopening/2.);
    double zm = (-mdist / 5. + 2.) + 1;

    for(int i = 0; i != rsize; ++i)
    {
        console->write("Point de repère à gauche à (" + QString::number(grefs[i].x()) + ", " + QString::number(grefs[i].y()) + ")");
        console->write("Repère associé à droite à (" + QString::number(drefs[i].x()) + ", " + QString::number(drefs[i].y()) + ")");

        double opening = REFMUR * (distance(grefs[i], drefs[i])) / distpixnorm;
        double dist = DISTOBJ * FOCAL / (opening/2.);

        double z = -dist / 5. + 2.;

        double distcm = (DISTMUR / 2.) + (z+1)*(DISTMUR / 2.) / zm;
        console->write_compl("Distance = " + QString::number(distcm) + "cm");

        double x = (double)(grefs[i].x() + drefs[i].x()) / (double)imgg->width() - 1;
        double y = -((double)(grefs[i].y() + drefs[i].y()) / (double)imgg->height() - 1);
        points.push_back(Point3D(distcm, x, y, z));
    }

    return points;
}
