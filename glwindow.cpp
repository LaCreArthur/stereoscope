
#include "glwindow.h"
#include "infoconsole.h"
#include "algorithm.h"

GLWindow::GLWindow(InfoConsole* c, const QVector < Point3D >& pts)
  : console(c), points(pts)
{
    this->setFixedSize(1000, 800);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    rot = 1;
    timer.start(16);
}

void GLWindow::initializeGL()
{
    glViewport(0, 0, this->width(), this->height());
    glClearColor(0, 0, 0, 1);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(rot > 0)
    {
        if(rot == ROT_MAX)
            rot = -1;
        else rot++;
    }
    else
    {
        if(rot == -ROT_MAX)
            rot = 1;
        else rot--;
    }

    glRotatef(0.5, (rot > 0) ? 1 : -1, (rot > 0) ? 1 : -1, 0.0);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);

        for(int i = 0; i < points.size()-2; ++i)
        {
            const Point3D& pt1 = points[i], pt2 = points[i+2];
            glVertex3f(pt1.x, pt1.y, pt1.z);
            glVertex3f(pt2.x, pt2.y, pt2.z);
        }

        /*
        for(int i = 0; i < points.size()-2; ++i)
        {
            const Point3D& pt1 = points[i], pt2 = points[i+1];
            glVertex3f(pt1.x, pt1.y, pt1.z);
            glVertex3f(pt2.x, pt2.y, pt2.z);
        }
        */

        for(int i = 0; i < points.size() / 2; ++i)
        {
            const Point3D& pt1 = points[2*i], pt2 = points[2*i+1];
            glVertex3f(pt1.x, pt1.y, pt1.z);
            glVertex3f(pt2.x, pt2.y, pt2.z);
        }

    glEnd();

    for(int i = 0; i < points.size(); ++i)
    {
        const Point3D& pt = points[i];
        glRasterPos3f(pt.x + 0.04, pt.y + 0.04, pt.z);
        QString dist = QString::number(pt.distcm) + "cm";
        for(int j = 0; j < dist.size(); ++j)

             glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, dist.toStdString()[j]);
    }
}
