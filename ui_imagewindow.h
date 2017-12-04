/********************************************************************************
** Form generated from reading UI file 'imagewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEWINDOW_H
#define UI_IMAGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageWindow
{
public:
    QAction *actionOuvrir_image_gauche;
    QAction *actionOuvrir_image_droite;
    QAction *actionQuitter;
    QAction *actionRubrique_d_aide;
    QAction *actionA_propos;
    QAction *actionLancer_la_reconstitution_3D;
    QAction *actionNouveau;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QLabel *label_gauche;
    QGroupBox *groupBox_2;
    QLabel *label_droite;
    QPushButton *go_button;
    QPushButton *load_imgg_button;
    QPushButton *load_imgd_button;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuAide;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImageWindow)
    {
        if (ImageWindow->objectName().isEmpty())
            ImageWindow->setObjectName(QStringLiteral("ImageWindow"));
        ImageWindow->resize(854, 392);
        actionOuvrir_image_gauche = new QAction(ImageWindow);
        actionOuvrir_image_gauche->setObjectName(QStringLiteral("actionOuvrir_image_gauche"));
        actionOuvrir_image_droite = new QAction(ImageWindow);
        actionOuvrir_image_droite->setObjectName(QStringLiteral("actionOuvrir_image_droite"));
        actionQuitter = new QAction(ImageWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionRubrique_d_aide = new QAction(ImageWindow);
        actionRubrique_d_aide->setObjectName(QStringLiteral("actionRubrique_d_aide"));
        actionA_propos = new QAction(ImageWindow);
        actionA_propos->setObjectName(QStringLiteral("actionA_propos"));
        actionLancer_la_reconstitution_3D = new QAction(ImageWindow);
        actionLancer_la_reconstitution_3D->setObjectName(QStringLiteral("actionLancer_la_reconstitution_3D"));
        actionNouveau = new QAction(ImageWindow);
        actionNouveau->setObjectName(QStringLiteral("actionNouveau"));
        centralWidget = new QWidget(ImageWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 341, 321));
        label_gauche = new QLabel(groupBox);
        label_gauche->setObjectName(QStringLiteral("label_gauche"));
        label_gauche->setGeometry(QRect(10, 30, 311, 281));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(500, 10, 341, 321));
        label_droite = new QLabel(groupBox_2);
        label_droite->setObjectName(QStringLiteral("label_droite"));
        label_droite->setGeometry(QRect(20, 30, 311, 281));
        go_button = new QPushButton(centralWidget);
        go_button->setObjectName(QStringLiteral("go_button"));
        go_button->setGeometry(QRect(360, 300, 131, 23));
        load_imgg_button = new QPushButton(centralWidget);
        load_imgg_button->setObjectName(QStringLiteral("load_imgg_button"));
        load_imgg_button->setGeometry(QRect(360, 30, 131, 23));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        load_imgg_button->setFont(font);
        load_imgd_button = new QPushButton(centralWidget);
        load_imgd_button->setObjectName(QStringLiteral("load_imgd_button"));
        load_imgd_button->setGeometry(QRect(360, 70, 131, 23));
        load_imgd_button->setFont(font);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(390, 140, 59, 15));
        QFont font1;
        font1.setPointSize(14);
        label->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(360, 160, 131, 16));
        QFont font2;
        font2.setPointSize(12);
        label_2->setFont(font2);
        ImageWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImageWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 854, 27));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuAide = new QMenu(menuBar);
        menuAide->setObjectName(QStringLiteral("menuAide"));
        ImageWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImageWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImageWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImageWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImageWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuAide->menuAction());
        menuFichier->addAction(actionNouveau);
        menuFichier->addAction(actionLancer_la_reconstitution_3D);
        menuFichier->addAction(actionOuvrir_image_gauche);
        menuFichier->addAction(actionOuvrir_image_droite);
        menuFichier->addAction(actionQuitter);
        menuAide->addAction(actionRubrique_d_aide);
        menuAide->addAction(actionA_propos);

        retranslateUi(ImageWindow);

        QMetaObject::connectSlotsByName(ImageWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ImageWindow)
    {
        ImageWindow->setWindowTitle(QApplication::translate("ImageWindow", "Vision St\303\251r\303\251oscopique", 0));
        actionOuvrir_image_gauche->setText(QApplication::translate("ImageWindow", "Ouvrir image gauche", 0));
        actionOuvrir_image_droite->setText(QApplication::translate("ImageWindow", "Ouvrir image droite", 0));
        actionQuitter->setText(QApplication::translate("ImageWindow", "Quitter", 0));
        actionRubrique_d_aide->setText(QApplication::translate("ImageWindow", "Rubrique d'aide", 0));
        actionA_propos->setText(QApplication::translate("ImageWindow", "A propos", 0));
        actionLancer_la_reconstitution_3D->setText(QApplication::translate("ImageWindow", "Lancer la reconstitution 3D", 0));
        actionNouveau->setText(QApplication::translate("ImageWindow", "Nouveau", 0));
        groupBox->setTitle(QApplication::translate("ImageWindow", "Image - prise de gauche", 0));
        label_gauche->setText(QString());
        groupBox_2->setTitle(QApplication::translate("ImageWindow", "Image - prise de droite", 0));
        label_droite->setText(QString());
        go_button->setText(QApplication::translate("ImageWindow", "C'est parti !", 0));
        load_imgg_button->setText(QApplication::translate("ImageWindow", "Ouvrir image gauche", 0));
        load_imgd_button->setText(QApplication::translate("ImageWindow", "Ouvrir image droite", 0));
        label->setText(QApplication::translate("ImageWindow", "Vision", 0));
        label_2->setText(QApplication::translate("ImageWindow", "St\303\251r\303\251oscopique", 0));
        menuFichier->setTitle(QApplication::translate("ImageWindow", "Fichier", 0));
        menuAide->setTitle(QApplication::translate("ImageWindow", "Divers", 0));
    } // retranslateUi

};

namespace Ui {
    class ImageWindow: public Ui_ImageWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEWINDOW_H
