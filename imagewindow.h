
#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QFileDialog>
#include <QSize>
#include <QMessageBox>

#define ADJ_WIDTH 500
#define ADJ_HEIGHT 300

namespace Ui {
class ImageWindow;
}

class InfoConsole;
class GLWindow;

class ImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = 0);

public slots:
    void nouveau();

    void ouvrir_image_gauche();
    void ouvrir_image_droite();

    void ouvrir_rubrique_aide();
    void ouvrir_a_propos();

    void go();

private:

    QImage* imgg;
    QImage* imgd;
    QSize other_size;

    Ui::ImageWindow *ui;

    InfoConsole* console;
    GLWindow* glWindow;

protected:
    void closeEvent(QCloseEvent*);
};

#endif // IMAGEWINDOW_H
