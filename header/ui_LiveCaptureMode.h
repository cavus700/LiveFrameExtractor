/********************************************************************************
** Form generated from reading UI file 'LiveCaptureMode.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIVECAPTUREMODE_H
#define UI_LIVECAPTUREMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LiveCaptureWidget
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *cbCameras;
    QPushButton *btnStartLive;
    QPushButton *btnStopLive;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnSaveDir;
    QLabel *lblSaveDir;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnStartRec;
    QPushButton *btnStopRec;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnStartExtr;
    QPushButton *btnStopExtr;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnLoadAreas;
    QLabel *lblLoadAreas;
    QPlainTextEdit *infoText;

    void setupUi(QWidget *LiveCaptureWidget)
    {
        if (LiveCaptureWidget->objectName().isEmpty())
            LiveCaptureWidget->setObjectName(QStringLiteral("LiveCaptureWidget"));
        LiveCaptureWidget->resize(677, 300);
        horizontalLayout_5 = new QHBoxLayout(LiveCaptureWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cbCameras = new QComboBox(LiveCaptureWidget);
        cbCameras->setObjectName(QStringLiteral("cbCameras"));

        horizontalLayout->addWidget(cbCameras);

        btnStartLive = new QPushButton(LiveCaptureWidget);
        btnStartLive->setObjectName(QStringLiteral("btnStartLive"));

        horizontalLayout->addWidget(btnStartLive);

        btnStopLive = new QPushButton(LiveCaptureWidget);
        btnStopLive->setObjectName(QStringLiteral("btnStopLive"));

        horizontalLayout->addWidget(btnStopLive);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnSaveDir = new QPushButton(LiveCaptureWidget);
        btnSaveDir->setObjectName(QStringLiteral("btnSaveDir"));

        horizontalLayout_3->addWidget(btnSaveDir);

        lblSaveDir = new QLabel(LiveCaptureWidget);
        lblSaveDir->setObjectName(QStringLiteral("lblSaveDir"));

        horizontalLayout_3->addWidget(lblSaveDir);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnStartRec = new QPushButton(LiveCaptureWidget);
        btnStartRec->setObjectName(QStringLiteral("btnStartRec"));

        horizontalLayout_4->addWidget(btnStartRec);

        btnStopRec = new QPushButton(LiveCaptureWidget);
        btnStopRec->setObjectName(QStringLiteral("btnStopRec"));

        horizontalLayout_4->addWidget(btnStopRec);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        btnStartExtr = new QPushButton(LiveCaptureWidget);
        btnStartExtr->setObjectName(QStringLiteral("btnStartExtr"));

        horizontalLayout_6->addWidget(btnStartExtr);

        btnStopExtr = new QPushButton(LiveCaptureWidget);
        btnStopExtr->setObjectName(QStringLiteral("btnStopExtr"));

        horizontalLayout_6->addWidget(btnStopExtr);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnLoadAreas = new QPushButton(LiveCaptureWidget);
        btnLoadAreas->setObjectName(QStringLiteral("btnLoadAreas"));

        horizontalLayout_2->addWidget(btnLoadAreas);

        lblLoadAreas = new QLabel(LiveCaptureWidget);
        lblLoadAreas->setObjectName(QStringLiteral("lblLoadAreas"));

        horizontalLayout_2->addWidget(lblLoadAreas);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout_2);

        infoText = new QPlainTextEdit(LiveCaptureWidget);
        infoText->setObjectName(QStringLiteral("infoText"));
        infoText->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infoText->sizePolicy().hasHeightForWidth());
        infoText->setSizePolicy(sizePolicy);
        infoText->setReadOnly(true);

        horizontalLayout_5->addWidget(infoText);


        retranslateUi(LiveCaptureWidget);

        QMetaObject::connectSlotsByName(LiveCaptureWidget);
    } // setupUi

    void retranslateUi(QWidget *LiveCaptureWidget)
    {
        LiveCaptureWidget->setWindowTitle(QApplication::translate("LiveCaptureWidget", "Form", 0));
        btnStartLive->setText(QApplication::translate("LiveCaptureWidget", "Start Livestream", 0));
        btnStopLive->setText(QApplication::translate("LiveCaptureWidget", "Stop Livestream", 0));
        btnSaveDir->setText(QApplication::translate("LiveCaptureWidget", "Save Directory", 0));
        lblSaveDir->setText(QApplication::translate("LiveCaptureWidget", "/tmp", 0));
        btnStartRec->setText(QApplication::translate("LiveCaptureWidget", "Start Recording", 0));
        btnStopRec->setText(QApplication::translate("LiveCaptureWidget", "Stop Recording", 0));
        btnStartExtr->setText(QApplication::translate("LiveCaptureWidget", "Start Extracting", 0));
        btnStopExtr->setText(QApplication::translate("LiveCaptureWidget", "Stop Extracting", 0));
        btnLoadAreas->setText(QApplication::translate("LiveCaptureWidget", "Load Settings", 0));
        lblLoadAreas->setText(QApplication::translate("LiveCaptureWidget", "/", 0));
    } // retranslateUi

};

namespace Ui {
    class LiveCaptureWidget: public Ui_LiveCaptureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIVECAPTUREMODE_H
