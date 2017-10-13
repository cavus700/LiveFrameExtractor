#include "header/VideoModeController.h"
#include "header/MainWindow.h"
#include "header/ImageScene.h"
#include "header/VideoController.h"
#include "header/JSONController.h"
#include "ui_VideoMode.h"
#include <iostream>

VideoWidget::VideoWidget(MainWindow *mw, QWidget *parent) :
    QWidget(parent),
    m_mw(mw),
    m_ui(new Ui::VideoWidget)
{
    m_ui->setupUi(this);
    initSIGNALSandSLOTS();
}

VideoWidget::~VideoWidget()
{
    if(m_vidController)
        delete m_vidController;
    delete m_ui;
}

void VideoWidget::initSIGNALSandSLOTS(){
    connect(m_ui->btnOpen , SIGNAL( clicked() ), this, SLOT( openVideoClicked() ));
    connect(m_ui->btnSaveDir , SIGNAL( clicked() ), this, SLOT( saveDirClicked() ));
    connect(m_ui->btnApply , SIGNAL( clicked() ), this, SLOT( applyCoeffClicked() ));
    connect(m_ui->btnRemove , SIGNAL( clicked() ), this, SLOT( removeCoeffClicked() ));
    connect(m_ui->btnAddArea , SIGNAL( clicked() ), this, SLOT( addAreaClicked() ));
    connect(m_ui->btnLoadSettings , SIGNAL( clicked() ), this, SLOT( loadSettingsClicked() ));
    connect(m_ui->btnDelArea , SIGNAL( clicked() ), this, SLOT( deleteAreaClicked() ));
    connect(m_ui->btnSaveSettings , SIGNAL( clicked() ), this, SLOT( saveSettingsClicked() ));
    connect(m_ui->btnSaveImg , SIGNAL( clicked() ), this, SLOT( saveImgsClicked() ));
    connect(m_ui->btnCancelSave , SIGNAL( clicked() ), this, SLOT( cancelSavingClicked() ));
    connect(m_ui->btnPlay , SIGNAL( clicked() ), this, SLOT( playClicked() ));
    connect(m_ui->btnStop , SIGNAL( clicked() ), this, SLOT( stopClicked() ));
    connect(m_ui->sldVideo , SIGNAL( valueChanged(int) ), this, SLOT( sliderMoved(int) ));

    connect(m_ui->editWidth, SIGNAL( textEdited(QString) ), this, SLOT( handleEditWidth(QString) ));
    connect(m_ui->editHeight, SIGNAL( textEdited(QString) ), this, SLOT( handleEditHeight(QString) ));
    connect(m_ui->editId, SIGNAL( textEdited(QString) ), this, SLOT( handleEditId(QString) ));
}

void VideoWidget::printInfo(QString str){
    auto doc = m_ui->infoText->document();
    doc->setPlainText(str + "\n" + doc->toPlainText() );
}

void VideoWidget::handleResize(){
    if(m_vidController)
        m_vidController->refreshImage();
}

void VideoWidget::sliderUpdate(double val){
    m_ui->sldVideo->setValue(static_cast<int>(val*100));
}

void VideoWidget::savingFinished(bool success){
    if(success){
        printInfo("Saving finished successfully");
    }
    else{
        printInfo("Saving canceled");
    }
    enableButtons();
    m_ui->btnPlay->setEnabled(true);
    m_ui->btnStop->setEnabled(true);
}

void VideoWidget::savingProgressUpdate(int prog){
    m_ui->savingProgress->setValue(prog);
}

void VideoWidget::openVideoClicked(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video Files (*.avi *.mpg *.mp4)"));
    if(filename.isEmpty())
        return;
    else{

        if(m_vidController){
            delete m_vidController;
            m_vidController = nullptr;
        }

        m_vidController = new VideoController();

        if (!m_vidController->loadVideo(filename.toUtf8().constData()))
        {    
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
            printInfo(QString("Video could not be loaded:\n") + filename); 
        }
    }
    
    QObject::connect(m_vidController, SIGNAL( processedImage(QImage) ), m_mw, SLOT( setImage(QImage) ));
    QObject::connect(m_vidController, SIGNAL( videoProgress(double) ), this, SLOT( sliderUpdate(double) ));
    QObject::connect(m_vidController, SIGNAL( savingProgress(int) ), this, SLOT( savingProgressUpdate(int) ));
    QObject::connect(m_vidController, SIGNAL( savingFinished(bool) ), this, SLOT( savingFinished(bool) ));
    QObject::connect(&m_mw->getImageScene(), SIGNAL( selectionChanged(QGraphicsRectItem) ), this, SLOT( showPropertys(QGraphicsRectItem) ));
    m_ui->lblOpen->setText(filename);
    m_mw->setImage(*m_vidController->getNextFrame());
    printInfo(QString("Video successfully loaded:\n") + filename);               
}

void VideoWidget::saveDirClicked(){
    QString dir = QFileDialog::getExistingDirectory ( this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dir != ""){
        m_ui->lblSaveDir->setText(dir);
    }
}

void VideoWidget::applyCoeffClicked(){
    using namespace cv;

    if(!m_vidController){
        printInfo("Error: Open a video first");
        return;
    }

    QString coeffStr = m_ui->editCamCoefficient->text();
    QStringList coeffStrArr = coeffStr.split(",");
    if(coeffStrArr.size() != 4){
        printInfo("Error: " + QString::number(coeffStr.size()) + " camera coefficients detected but 4 required");
        return;
    }

    QString distStr = m_ui->editDistCoefficient->text();
    QStringList distStrArr = distStr.split(",");
    if(distStrArr.size() != 5){
        printInfo("Error: " + QString::number(distStr.size()) + " distortion coefficients detected but 5 required");
        return;
    }

    Mat intrinsic = Mat(3, 3, CV_32FC1);
    Mat distCoeffs = Mat(1, 5, CV_32FC1);

    intrinsic.ptr<float>(0)[0] = coeffStrArr[0].toFloat();
    intrinsic.ptr<float>(0)[1] = 0.0f;
    intrinsic.ptr<float>(0)[2] = coeffStrArr[1].toFloat();
    intrinsic.ptr<float>(1)[0] = 0.0f;
    intrinsic.ptr<float>(1)[1] = coeffStrArr[2].toFloat();
    intrinsic.ptr<float>(1)[2] = coeffStrArr[3].toFloat();
    intrinsic.ptr<float>(2)[0] = 0.0f;
    intrinsic.ptr<float>(2)[1] = 0.0f;
    intrinsic.ptr<float>(2)[2] = 1.0f;

    distCoeffs.ptr<float>(0)[0] = distStrArr[0].toFloat();
    distCoeffs.ptr<float>(0)[1] = distStrArr[1].toFloat();
    distCoeffs.ptr<float>(0)[2] = distStrArr[2].toFloat();
    distCoeffs.ptr<float>(0)[3] = distStrArr[3].toFloat();
    distCoeffs.ptr<float>(0)[4] = distStrArr[4].toFloat();

    QString printMat = QString("Camera Matrix:\n");
    printMat += QString::number(intrinsic.ptr<float>(0)[0]) + "  " + QString::number(intrinsic.ptr<float>(0)[1]) + "  " + QString::number(intrinsic.ptr<float>(0)[2]) + "\n";
    printMat += QString::number(intrinsic.ptr<float>(1)[0]) + "  " + QString::number(intrinsic.ptr<float>(1)[1]) + "  " + QString::number(intrinsic.ptr<float>(1)[2]) + "\n";
    printMat += QString::number(intrinsic.ptr<float>(2)[0]) + "  " + QString::number(intrinsic.ptr<float>(2)[1]) + "  " + QString::number(intrinsic.ptr<float>(2)[2]) + "\n\n";
    printMat += "Distortion Matrix:\n";
    printMat += QString::number(distCoeffs.ptr<float>(0)[0]) + "  " + QString::number(distCoeffs.ptr<float>(0)[1]) + "  " + QString::number(distCoeffs.ptr<float>(0)[2]) + "  " + QString::number(distCoeffs.ptr<float>(0)[3]) + "  " + QString::number(distCoeffs.ptr<float>(0)[4]);
    printInfo("Matrices applyed:\n" + printMat);

    VideoController::CameraParameters para;
    para.intrinsic = intrinsic;
    para.distortion = distCoeffs;
    m_vidController->setCameraParameters(para);
}

void VideoWidget::removeCoeffClicked(){
    if(m_vidController){
        m_vidController->removeCameraParameters();
        printInfo("Camera parameters removed");
    }
}

void VideoWidget::addAreaClicked(){
    if(m_mw->getImageScene().addRectangle()) {
        printInfo(QString("New area added"));
    }
    else{
        printInfo(QString("Couldn't add new area. Maybe you added already 50 areas?"));
    }
}

void VideoWidget::deleteAreaClicked(){
    printInfo(m_mw->getImageScene().removeRectangle());
}

void VideoWidget::saveSettingsClicked(){
    if(!m_vidController || m_vidController->getImage() == nullptr){
        printInfo("Error: Can't save video areas without loaded video");
        return;
    }
    
    //Save Area
    JSONController::saveAreas(m_mw->getImageScene().getRectangles(), 
                        m_mw->getImageScene().getImgWidth(), 
                        m_mw->getImageScene().getImgHeight(), 
                        m_ui->lblSaveDir->text());
    //Save parameters
    if(m_vidController){
        VideoController::CameraParameters* params = m_vidController->getCameraParameters();
        if(params){
            JSONController::saveParameters(*params, m_ui->lblSaveDir->text());
        }
    }
    
    //Save offset
    JSONController::saveTimeOffset(m_ui->editOffset->text().toInt(), m_ui->lblSaveDir->text());

    //Save size
    JSONController::saveSize(m_ui->spinSize->value(), m_ui->lblSaveDir->text());

    printInfo(QString("Settings successfully saved to ") + m_ui->lblSaveDir->text() + FILE_NAME);
}

void VideoWidget::loadSettingsClicked(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Area File (*.json)"));
    if(filename.isEmpty())
        return;
    
    if(!m_vidController || m_vidController->getImage() == nullptr){
        printInfo("Error: Can't load video settings without loaded video");
        return;
    }

    //Load areas
    auto rectList = JSONController::loadAreas(filename, m_mw->getImageScene().getImgWidth(), m_mw->getImageScene().getImgHeight());
    if(rectList->size() == 0){
        printInfo("Error: Couldn't load areas. Maybe the json file doesn't contain any or it is invalid");
        return;
    }
    m_mw->getImageScene().setRectangles(*rectList);
    m_vidController->refreshImage();
    m_ui->editWidth->clear();
    m_ui->editHeight->clear();
    m_ui->editId->clear();

    //Load time offset
    m_ui->editOffset->clear();
    m_ui->editOffset->setText(QString::number(JSONController::loadTimeOffset(filename)));
    
    //Load size 
    int size = JSONController::loadSize(filename);
    if(size == -1)
        size = 48;
    m_ui->spinSize->setValue(size);

    //Load parameters
    VideoController::CameraParameters params;
    m_ui->editCamCoefficient->clear();
    m_ui->editDistCoefficient->clear();
    if(JSONController::loadParameters(filename, params)){
        QString cam = "";
        cam += QString::number(params.intrinsic.ptr<float>(0)[0]) + ",";
        cam += QString::number(params.intrinsic.ptr<float>(0)[2]) + ",";
        cam += QString::number(params.intrinsic.ptr<float>(1)[1]) + ",";
        cam += QString::number(params.intrinsic.ptr<float>(1)[2]);
        m_ui->editCamCoefficient->setText(cam);

        QString dist = "";
        for(int iCol = 0; iCol < 5; iCol++){
            dist += QString::number(params.distortion.ptr<float>(0)[iCol]) + ",";
        }
        dist = dist.mid(0, dist.size() - 1);
        m_ui->editDistCoefficient->setText(dist);
        if(m_vidController)
            m_vidController->setCameraParameters(params);
    }
    else{
        printInfo("Error: No parameters loaded. Invalid format or not saved");
    }
    printInfo("Settings from " + filename + " successfully loaded!");
}

void VideoWidget::saveImgsClicked(){
    if(!m_vidController){
        printInfo("Error: Load a video first");
        return;
    }
    if(m_ui->editOffset->text().toInt() <= 0){
        printInfo("Error: Time offset has to be greater than 0");
        return;
    }

    disableButtons();
    m_ui->btnCancelSave->setEnabled(true);
    m_ui->btnPlay->setEnabled(false);
    m_ui->btnStop->setEnabled(false);
    m_vidController->saveImages(m_mw->getImageScene().getRectangles(), 
                                m_mw->getImageViewSize(),
                                m_ui->editOffset->text().toInt(), 
                                m_ui->spinSize->value(),
                                m_ui->lblSaveDir->text());
}

void VideoWidget::cancelSavingClicked(){
    if(m_vidController)
        m_vidController->stopSaving();
}

void VideoWidget::enableButtons(){
    m_ui->btnOpen->setEnabled(true);
    m_ui->btnStop->setEnabled(false);
    m_ui->btnSaveDir->setEnabled(true);
    m_ui->btnApply->setEnabled(true);
    m_ui->btnRemove->setEnabled(true);
    m_ui->btnSaveSettings->setEnabled(true);
    m_ui->btnCancelSave->setEnabled(true);
    m_ui->btnSaveImg->setEnabled(true);
    m_ui->btnAddArea->setEnabled(true);
    m_ui->btnDelArea->setEnabled(true);
    m_ui->btnLoadSettings->setEnabled(true);
    m_mw->getImageScene().setEnableDragMode(true);
}

void VideoWidget::disableButtons(){
    m_ui->btnOpen->setEnabled(false);
    m_ui->btnPlay->setEnabled(false);
    m_ui->btnSaveDir->setEnabled(false);
    m_ui->btnApply->setEnabled(false);
    m_ui->btnRemove->setEnabled(false);
    m_ui->btnSaveSettings->setEnabled(false);
    m_ui->btnSaveImg->setEnabled(false);
    m_ui->btnCancelSave->setEnabled(false);
    m_ui->btnAddArea->setEnabled(false);
    m_ui->btnDelArea->setEnabled(false);
    m_ui->btnLoadSettings->setEnabled(false);
    m_mw->getImageScene().setEnableDragMode(false);
}

void VideoWidget::playClicked(){
    if(!m_vidController)
        return;

    if (m_vidController->isStopped())
    {
        m_vidController->Play();
        m_ui->sldVideo->setEnabled(false);
        m_ui->btnStop->setEnabled(true);
        disableButtons();
        printInfo(QString("Play video..."));
    }
}

void VideoWidget::stopClicked(){
    if(!m_vidController)
        return;

    if (!m_vidController->isStopped())
    {
        m_vidController->Stop();
        m_ui->sldVideo->setEnabled(true);
        m_ui->btnPlay->setEnabled(true);
        enableButtons();
        printInfo(QString("Stop video..."));
    }
}

void VideoWidget::sliderMoved(int val){
    if(!m_vidController->isStopped()){
        //check if video finished
        if(val == m_ui->sldVideo->maximum())
            enableButtons();

        return;
    }
    double pos = static_cast<double>(val) / static_cast<double>(m_ui->sldVideo->maximum());
    m_vidController->setPosition(pos);
}

void VideoWidget::handleEditWidth(QString text){
    m_mw->getImageScene().resizeRectangle(text.toInt(), m_ui->editHeight->text().toInt());
}

void VideoWidget::handleEditHeight(QString text){
    m_mw->getImageScene().resizeRectangle(m_ui->editWidth->text().toInt(), text.toInt());
}

void VideoWidget::handleEditId(QString text){
    m_mw->getImageScene().renameRectangle(text);
}

void VideoWidget::showPropertys(const QGraphicsRectItem& rectItem){
    m_ui->editWidth->clear();
    m_ui->editHeight->clear();
    m_ui->editWidth->insert(QString::number(rectItem.rect().width()));
    m_ui->editHeight->insert(QString::number(rectItem.rect().height()));
    m_ui->editId->clear();
    m_ui->editId->insert(rectItem.toolTip());
}