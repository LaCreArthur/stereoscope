        #ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>
#include <QVector>
#include <GL/glut.h>

#include <QTimer>

#define ROT_MAX 70

class InfoConsole;
class Point3D;

class GLWindow : public QGLWidget
{
public:
    GLWindow(InfoConsole*, const QVector < Point3D >&);

    void initializeGL();
    void paintGL();

private:
    InfoConsole* console;
    QVector < Point3D > points;
    int rot;

    QTimer timer; /** A EFFACER **/
};

#endif // GLWINDOW_H
