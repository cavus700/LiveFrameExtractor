/********************************************************************************
** Form generated from reading UI file 'VideoMode.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOMODE_H
#define UI_VIDEOMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QPushButton *btnOpen;
    QLabel *lblOpen;
    QPushButton *btnSaveDir;
    QLabel *lblSaveDir;
    QPushButton *btnSaveSettings;
    QPushButton *btnLoadSettings;
    QFrame *frame;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLineEdit *editCamCoefficient;
    QLabel *label_4;
    QLineEdit *editDistCoefficient;
    QPushButton *btnApply;
    QPushButton *btnRemove;
    QFrame *frame_4;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_8;
    QLineEdit *editOffset;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_2;
    QSpinBox *spinSize;
    QPushButton *btnSaveImg;
    QPushButton *btnCancelSave;
    QProgressBar *savingProgress;
    QFrame *frame_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLineEdit *editId;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_7;
    QLineEdit *editHeight;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QLineEdit *editWidth;
    QPushButton *btnAddArea;
    QPushButton *btnDelArea;
    QHBoxLayout *horizontalLayout_3;
    QSlider *sldVideo;
    QPushButton *btnPlay;
    QPushButton *btnStop;
    QPlainTextEdit *infoText;

    void setupUi(QWidget *VideoWidget)
    {
        if (VideoWidget->objectName().isEmpty())
            VideoWidget->setObjectName(QStringLiteral("VideoWidget"));
        VideoWidget->resize(520, 580);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VideoWidget->sizePolicy().hasHeightForWidth());
        VideoWidget->setSizePolicy(sizePolicy);
        VideoWidget->setMaximumSize(QSize(520, 16777215));
        verticalLayout_3 = new QVBoxLayout(VideoWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(VideoWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        btnOpen = new QPushButton(groupBox);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnOpen->sizePolicy().hasHeightForWidth());
        btnOpen->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(btnOpen);

        lblOpen = new QLabel(groupBox);
        lblOpen->setObjectName(QStringLiteral("lblOpen"));
        lblOpen->setTextFormat(Qt::AutoText);
        lblOpen->setScaledContents(true);
        lblOpen->setWordWrap(true);

        verticalLayout_6->addWidget(lblOpen);

        btnSaveDir = new QPushButton(groupBox);
        btnSaveDir->setObjectName(QStringLiteral("btnSaveDir"));

        verticalLayout_6->addWidget(btnSaveDir);

        lblSaveDir = new QLabel(groupBox);
        lblSaveDir->setObjectName(QStringLiteral("lblSaveDir"));
        lblSaveDir->setScaledContents(true);
        lblSaveDir->setWordWrap(true);

        verticalLayout_6->addWidget(lblSaveDir);

        btnSaveSettings = new QPushButton(groupBox);
        btnSaveSettings->setObjectName(QStringLiteral("btnSaveSettings"));

        verticalLayout_6->addWidget(btnSaveSettings);

        btnLoadSettings = new QPushButton(groupBox);
        btnLoadSettings->setObjectName(QStringLiteral("btnLoadSettings"));

        verticalLayout_6->addWidget(btnLoadSettings);

        lblOpen->raise();
        btnSaveDir->raise();
        btnOpen->raise();
        lblSaveDir->raise();
        btnLoadSettings->raise();
        btnSaveSettings->raise();

        horizontalLayout->addWidget(groupBox);

        frame = new QFrame(VideoWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::VLine);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(3);

        horizontalLayout->addWidget(frame);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        groupBox_2 = new QGroupBox(VideoWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        editCamCoefficient = new QLineEdit(groupBox_2);
        editCamCoefficient->setObjectName(QStringLiteral("editCamCoefficient"));

        verticalLayout->addWidget(editCamCoefficient);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        editDistCoefficient = new QLineEdit(groupBox_2);
        editDistCoefficient->setObjectName(QStringLiteral("editDistCoefficient"));

        verticalLayout->addWidget(editDistCoefficient);

        btnApply = new QPushButton(groupBox_2);
        btnApply->setObjectName(QStringLiteral("btnApply"));

        verticalLayout->addWidget(btnApply);

        btnRemove = new QPushButton(groupBox_2);
        btnRemove->setObjectName(QStringLiteral("btnRemove"));

        verticalLayout->addWidget(btnRemove);


        verticalLayout_7->addWidget(groupBox_2);

        frame_4 = new QFrame(VideoWidget);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::HLine);
        frame_4->setFrameShadow(QFrame::Raised);

        verticalLayout_7->addWidget(frame_4);

        groupBox_4 = new QGroupBox(VideoWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_8 = new QVBoxLayout(groupBox_4);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setScaledContents(false);
        label_8->setAlignment(Qt::AlignCenter);
        label_8->setWordWrap(true);

        verticalLayout_9->addWidget(label_8);

        editOffset = new QLineEdit(groupBox_4);
        editOffset->setObjectName(QStringLiteral("editOffset"));

        verticalLayout_9->addWidget(editOffset);


        horizontalLayout_4->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_10->addWidget(label_2);

        spinSize = new QSpinBox(groupBox_4);
        spinSize->setObjectName(QStringLiteral("spinSize"));
        spinSize->setMinimum(48);
        spinSize->setMaximum(256);

        verticalLayout_10->addWidget(spinSize);


        horizontalLayout_4->addLayout(verticalLayout_10);


        verticalLayout_8->addLayout(horizontalLayout_4);

        btnSaveImg = new QPushButton(groupBox_4);
        btnSaveImg->setObjectName(QStringLiteral("btnSaveImg"));

        verticalLayout_8->addWidget(btnSaveImg);

        btnCancelSave = new QPushButton(groupBox_4);
        btnCancelSave->setObjectName(QStringLiteral("btnCancelSave"));

        verticalLayout_8->addWidget(btnCancelSave);

        savingProgress = new QProgressBar(groupBox_4);
        savingProgress->setObjectName(QStringLiteral("savingProgress"));
        savingProgress->setEnabled(false);
        savingProgress->setValue(0);

        verticalLayout_8->addWidget(savingProgress);


        verticalLayout_7->addWidget(groupBox_4);


        horizontalLayout->addLayout(verticalLayout_7);

        frame_2 = new QFrame(VideoWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::VLine);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(3);

        horizontalLayout->addWidget(frame_2);

        groupBox_3 = new QGroupBox(VideoWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(label);

        editId = new QLineEdit(groupBox_3);
        editId->setObjectName(QStringLiteral("editId"));

        verticalLayout_2->addWidget(editId);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(label_7);

        editHeight = new QLineEdit(groupBox_3);
        editHeight->setObjectName(QStringLiteral("editHeight"));

        verticalLayout_5->addWidget(editHeight);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);

        verticalLayout_4->addWidget(label_6);

        editWidth = new QLineEdit(groupBox_3);
        editWidth->setObjectName(QStringLiteral("editWidth"));

        verticalLayout_4->addWidget(editWidth);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_2);

        btnAddArea = new QPushButton(groupBox_3);
        btnAddArea->setObjectName(QStringLiteral("btnAddArea"));

        verticalLayout_2->addWidget(btnAddArea);

        btnDelArea = new QPushButton(groupBox_3);
        btnDelArea->setObjectName(QStringLiteral("btnDelArea"));

        verticalLayout_2->addWidget(btnDelArea);


        horizontalLayout->addWidget(groupBox_3);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        sldVideo = new QSlider(VideoWidget);
        sldVideo->setObjectName(QStringLiteral("sldVideo"));
        sldVideo->setEnabled(false);
        sldVideo->setMaximum(100);
        sldVideo->setTracking(false);
        sldVideo->setOrientation(Qt::Horizontal);
        sldVideo->setTickPosition(QSlider::NoTicks);

        horizontalLayout_3->addWidget(sldVideo);

        btnPlay = new QPushButton(VideoWidget);
        btnPlay->setObjectName(QStringLiteral("btnPlay"));

        horizontalLayout_3->addWidget(btnPlay);

        btnStop = new QPushButton(VideoWidget);
        btnStop->setObjectName(QStringLiteral("btnStop"));

        horizontalLayout_3->addWidget(btnStop);


        verticalLayout_3->addLayout(horizontalLayout_3);

        infoText = new QPlainTextEdit(VideoWidget);
        infoText->setObjectName(QStringLiteral("infoText"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(infoText->sizePolicy().hasHeightForWidth());
        infoText->setSizePolicy(sizePolicy3);
        infoText->setReadOnly(true);

        verticalLayout_3->addWidget(infoText);


        retranslateUi(VideoWidget);

        QMetaObject::connectSlotsByName(VideoWidget);
    } // setupUi

    void retranslateUi(QWidget *VideoWidget)
    {
        VideoWidget->setWindowTitle(QApplication::translate("VideoWidget", "Form", 0));
        groupBox->setTitle(QApplication::translate("VideoWidget", "In-/Output", 0));
        btnOpen->setText(QApplication::translate("VideoWidget", "Open Video", 0));
        lblOpen->setText(QApplication::translate("VideoWidget", "/home", 0));
        btnSaveDir->setText(QApplication::translate("VideoWidget", "Save Directory", 0));
        lblSaveDir->setText(QApplication::translate("VideoWidget", "/tmp", 0));
        btnSaveSettings->setText(QApplication::translate("VideoWidget", "Save Settings", 0));
        btnLoadSettings->setText(QApplication::translate("VideoWidget", "Load Settings", 0));
        groupBox_2->setTitle(QApplication::translate("VideoWidget", "Coefficients", 0));
        label_3->setText(QApplication::translate("VideoWidget", "Camera coefficients", 0));
#ifndef QT_NO_TOOLTIP
        editCamCoefficient->setToolTip(QApplication::translate("VideoWidget", "Enter the comma seperated camera coefficients", 0));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("VideoWidget", "Distortion coefficients", 0));
#ifndef QT_NO_TOOLTIP
        editDistCoefficient->setToolTip(QApplication::translate("VideoWidget", "Enter the comma seperated distortion coefficients", 0));
#endif // QT_NO_TOOLTIP
        btnApply->setText(QApplication::translate("VideoWidget", "Apply coefficients", 0));
        btnRemove->setText(QApplication::translate("VideoWidget", "Remove coefficients", 0));
#ifndef QT_NO_TOOLTIP
        groupBox_4->setToolTip(QApplication::translate("VideoWidget", "Saved images will be resized to NxN", 0));
#endif // QT_NO_TOOLTIP
        groupBox_4->setTitle(QApplication::translate("VideoWidget", "GroupBox", 0));
        label_8->setText(QApplication::translate("VideoWidget", "Time offset", 0));
#ifndef QT_NO_TOOLTIP
        editOffset->setToolTip(QApplication::translate("VideoWidget", "Set the time offset for image extraction in msec", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("VideoWidget", "Size", 0));
#ifndef QT_NO_TOOLTIP
        spinSize->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnSaveImg->setText(QApplication::translate("VideoWidget", "Save Images", 0));
        btnCancelSave->setText(QApplication::translate("VideoWidget", "Cancel saving", 0));
        groupBox_3->setTitle(QApplication::translate("VideoWidget", "Editing", 0));
        label->setText(QApplication::translate("VideoWidget", "Area name (ID)", 0));
        label_7->setText(QApplication::translate("VideoWidget", "Height", 0));
        label_6->setText(QApplication::translate("VideoWidget", "Width", 0));
        btnAddArea->setText(QApplication::translate("VideoWidget", "Add Area", 0));
        btnDelArea->setText(QApplication::translate("VideoWidget", "Delete Area", 0));
        btnPlay->setText(QApplication::translate("VideoWidget", "Play", 0));
        btnStop->setText(QApplication::translate("VideoWidget", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoWidget: public Ui_VideoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOMODE_H
