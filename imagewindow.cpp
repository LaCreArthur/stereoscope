
#include "imagewindow.h"
#include "infoconsole.h"
#include "glwindow.h"
#include "algorithm.h"

#include "ui_imagewindow.h"
#include "ui_console.h"

// Constructeur et destructeur

ImageWindow::ImageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageWindow),
    console(new InfoConsole),
    glWindow(0)
{
    ui->setupUi(this);
    this->setFixedSize(854, 392);

    // Affichage de la console informative
    console->show();

    this->nouveau();

    // Gestion des évènements
    // Ouverture des images
    connect(ui->load_imgg_button, SIGNAL(clicked()), this, SLOT(ouvrir_image_gauche()));
    connect(ui->load_imgd_button, SIGNAL(clicked()), this, SLOT(ouvrir_image_droite()));

    // Connection des onglets
    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(nouveau()));

    connect(ui->actionOuvrir_image_gauche, SIGNAL(triggered()), this, SLOT(ouvrir_image_gauche()));
    connect(ui->actionOuvrir_image_droite, SIGNAL(triggered()), this, SLOT(ouvrir_image_droite()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->actionRubrique_d_aide, SIGNAL(triggered()), this, SLOT(ouvrir_rubrique_aide()));
    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(ouvrir_a_propos()));

    connect(ui->actionLancer_la_reconstitution_3D, SIGNAL(triggered()), this, SLOT(go()));

    // Lancement de la reconstitution 3D
    connect(ui->go_button, SIGNAL(clicked()), this, SLOT(go()));
}

void ImageWindow::closeEvent(QCloseEvent* e)
{
    QMainWindow::closeEvent(e);
    delete ui;

    // Si on a fermé la fenêtre principale, on ferme également toutes les fenêtres annexes (console et affichage 3D)
    delete console;
    delete glWindow;
}

// Créer une nouvelle session d'utilisation

void ImageWindow::nouveau()
{
    delete glWindow;
    glWindow = 0;

    other_size = QSize(0, 0);
    imgg = imgd = 0;
    ui->label_gauche->clear();
    ui->label_droite->clear();

    console->clear();
    console->write("Bienvenu !");
    console->write_compl("Programme développé par OStrebler & AScheidel");
}

// Ouverture des deux images stereoscopiques

void ImageWindow::ouvrir_image_gauche()
{
    // Sélection du chemin de l'image à ouvrir
    QString img_path = QFileDialog::getOpenFileName(this, "Ouvrir l'image de gauche", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

    if(!img_path.isNull())
    {
        // Chargement de l'image
        QImage gauche(img_path);
        imgg = new QImage(gauche/*.scaled(ADJ_WIDTH, ADJ_HEIGHT)*/);

        // Si l'autre image est déjà chargée et que ses dimensions ne sont pas les mêmes...
        if(imgd && (gauche.height() != other_size.height() || gauche.width() != other_size.width()))
        {
            console->write_error("le chargement de l'image gauche a échoué");

            QString error_compl = "Tailles : "
                 + QString::number(gauche.width()) + " * " + QString::number(gauche.height())
                 + " vs "
                 + QString::number(other_size.width()) + " * " + QString::number(other_size.height());

            console->write_error_compl(error_compl);
            QMessageBox::critical(this, "Erreur", "L'image gauche doit avoir les mêmes dimensions que l'image droite !");

            ui->label_gauche->clear();
            imgg = 0;
            delete glWindow;
            glWindow = 0;
        }
        else // Sinon ok
        {
            other_size = gauche.size();

            // Il est important de convenir d'un format, car la manipulation de l'image
            // va en dépendre (les fonctions ne sont pas les mêmes suivant le format)
            *imgg = imgg->convertToFormat(QImage::Format_RGB32);


            // On affiche une version redimensionnée de l'image
            ui->label_gauche->setPixmap(QPixmap::fromImage(*imgg).scaled(ui->label_gauche->size()));
            console->write("Chargement de l'image gauche réussi");
            console->write_compl("Taille : " + QString::number(gauche.width()) + " * " + QString::number(gauche.height()));
        }
    }
}

void ImageWindow::ouvrir_image_droite()
{
    QString img_path = QFileDialog::getOpenFileName(this, "Ouvrir l'image de droite", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

    if(!img_path.isNull())
    {
        QImage droite(img_path);
        imgd = new QImage(droite/*.scaled(ADJ_WIDTH, ADJ_HEIGHT)*/);

        if(imgg && (droite.height() != other_size.height() || droite.width() != other_size.width()))
        {
            console->write_error("le chargement de l'image droite a échoué");

            QString error_compl = "Tailles : "
                 + QString::number(droite.width()) + " * " + QString::number(droite.height())
                 + " vs "
                 + QString::number(other_size.width()) + " * " + QString::number(other_size.height());

            console->write_error_compl(error_compl);
            QMessageBox::critical(this, "Erreur", "L'image droite doit avoir les mêmes dimensions que l'image gauche !");

            ui->label_droite->clear();
            imgd = 0;
            delete glWindow;
            glWindow = 0;
        }
        else
        {
            other_size = droite.size();

            *imgd = imgd->convertToFormat(QImage::Format_RGB32);
            ui->label_droite->setPixmap(QPixmap::fromImage(*imgd).scaled(ui->label_droite->size()));

            console->write("Chargement de l'image droite réussi");
            console->write_compl("Taille : " + QString::number(droite.width()) + " * " + QString::number(droite.height()) + "");
        }
    }
}

// Lancer la reconstitution 3D

void ImageWindow::go()
{
    delete glWindow;
    glWindow = 0;

    // Impossible de démarrer la reconstitution 3D si l'une ou les deux image(s) manque(nt)
    if(!imgg || !imgd)
    {
        console->write_error("impossible de lancer la reconstitution 3D");
        console->write_error_compl("Source manquante");
        QMessageBox::critical(this, "Erreur", "Il charger les DEUX images avant de lancer la reconstitution 3D !");
    }
    else // Sinon ok
    {
        console->write("Reconstitution 3D en cours...");

        Algorithm algo(console, imgg, imgd);

        // algo.go() envoie l'ensemble des pixels 3D formant la scène reconstituée à glWindow qui les affichent
        try
        {
            glWindow = new GLWindow(console, algo.go());
            glWindow->show();
        }
        catch(...)
        {
        }

        console->write("Fin de la reconstitution");
    }
}

// Rubrique d'aide et A propos

void ImageWindow::ouvrir_rubrique_aide()
{
    QString msg =
        "Chargez deux images correspondant à deux prises stéréoscopiques d'une même scène et "
        "appuyez sur \"C'est parti !\" pour calculer la reconstitution 3D de la scène !\n\n"
        "Vous pouvez alors vous déplacer dans l'espace connu de la scène en utilisant la souris ou les touches directionnelles "
        "et apprécier l'effet 3D de la reconstitution.";

    QMessageBox::information(this, "Rubrique d'aide", msg);
}

void ImageWindow::ouvrir_a_propos()
{
    QString msg =
        "Programme développé en C++ (Qt) par Olivier Strebler et Arthur Scheidel "
        "dans le cadre du projet de POO de L3S5 Automne 2014 - Université de Strasbourg.";

    QMessageBox::information(this, "A propos", msg);
}
