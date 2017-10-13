/********************************************************************************
** Form generated from reading UI file 'LiveFrameExtractorUI.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVEFRAMEEXTRACTORUI_H
#define UI_LIVEFRAMEEXTRACTORUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridMain;
    QRadioButton *btnV;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *btnLC;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(612, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridMain = new QGridLayout();
        gridMain->setObjectName(QStringLiteral("gridMain"));
        gridMain->setSizeConstraint(QLayout::SetDefaultConstraint);
        btnV = new QRadioButton(centralwidget);
        btnV->setObjectName(QStringLiteral("btnV"));
        btnV->setAutoFillBackground(false);

        gridMain->addWidget(btnV, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridMain->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridMain->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        btnLC = new QRadioButton(centralwidget);
        btnLC->setObjectName(QStringLiteral("btnLC"));
        btnLC->setAutoFillBackground(false);

        gridMain->addWidget(btnLC, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridMain->addItem(horizontalSpacer, 0, 0, 1, 1);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridMain->addWidget(graphicsView, 1, 0, 1, 5);


        verticalLayout->addLayout(gridMain);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 612, 28));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LiveFrameExtractor", 0));
        btnV->setText(QApplication::translate("MainWindow", "Video Mode", 0));
        btnLC->setText(QApplication::translate("MainWindow", "Live Capture Mode", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVEFRAMEEXTRACTORUI_H
