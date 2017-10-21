#include "header/LiveCaptureModeController.h"
#include "header/LiveCameraController.h"
#include "header/MainWindow.h"
#include "header/ImageScene.h"
#include "ui_LiveCaptureMode.h"

LiveCaptureWidget::LiveCaptureWidget(MainWindow *mw, QWidget *parent) :
    QWidget(parent),
    m_mw(mw),
    m_ui(new Ui::LiveCaptureWidget),
    m_currentCamera(nullptr)
{
    m_ui->setupUi(this);
    initSIGNALSandSLOTS();

    //search for cameras in /dev/
    QDir* dir = new QDir("/dev/", "", QDir::Name, QDir::System);
    dir->setNameFilters(QStringList()<<"video?");
    QStringList vidDevList = dir->entryList();
    //For every found camera 
    for(QString dev: vidDevList){
        //Add camera to combobox and save it in list 
        m_ui->cbCameras->addItem(dev);
        m_cameras.push_back(CameraContainer(dev, dev.mid(dev.size() - 1).toInt()));
        printInfo("Loaded camera: " + m_cameras.back().name + "(" + QString::number(m_cameras.back().id) + ")");
    }

    if(m_cameras.size() == 0){
        printInfo("Error: No cameras detected");
    }
    else{
        //If one or more camera was found take the first, init, load and connect it
        printInfo(QString::number(m_cameras.size()) + " camera(s) detected" );
        m_currentCamera = &m_cameras.front();
        initCameraContainer(*m_currentCamera);
        loadCameraContainer(*m_currentCamera);
        connect(m_currentCamera->controller, SIGNAL( processedImage(QImage) ), m_mw, SLOT( setImage(QImage) ));
    }
}

LiveCaptureWidget::~LiveCaptureWidget()
{
    if(m_currentCamera && m_currentCamera->isInit())
                disconnect(m_currentCamera->controller, SIGNAL( processedImage(QImage) ), m_mw, SLOT( setImage(QImage) ));
           
    for(auto& con : m_cameras){
        if(con.isInit()){
            unloadCamerContainer(con);
        }
    }
    m_cameras.clear();
    delete m_ui;
}

void LiveCaptureWidget::initSIGNALSandSLOTS(){
    connect(m_ui->btnStartLive, SIGNAL( clicked() ), this, SLOT ( startLivestreamCLicked() ));
    connect(m_ui->btnStopLive, SIGNAL( clicked() ), this, SLOT ( stopLivestreamClicked() ));
    connect(m_ui->btnLoadAreas, SIGNAL( clicked() ), this, SLOT ( loadAreasClicked() ));
    connect(m_ui->btnSaveDir, SIGNAL( clicked() ), this, SLOT ( saveDirClicked() ));
    connect(m_ui->btnStartExtr, SIGNAL( clicked() ), this, SLOT ( startExtrClicked() ));
    connect(m_ui->btnStopExtr, SIGNAL( clicked() ), this, SLOT ( stopExtrClicked() ));
    connect(m_ui->btnStartRec, SIGNAL( clicked() ), this, SLOT ( startRecClicked() ));
    connect(m_ui->btnStopRec, SIGNAL( clicked() ), this, SLOT ( stopRecClicked() ));
    connect(m_ui->cbCameras, SIGNAL( currentIndexChanged(QString) ), this, SLOT( handleCameraChanged(QString) ));
}

void LiveCaptureWidget::printInfo(QString str){
    QString cam = "";
    if(m_currentCamera && m_currentCamera->isInit()){
        cam = "(" + QString::number(m_currentCamera->controller->getSettings().cameraId) + ") ";
    }
    auto doc = m_ui->infoText->document();
    doc->setPlainText(cam + str + "\n" + doc->toPlainText() );
}

void LiveCaptureWidget::handleCameraChanged(QString camera){
    if(m_cameras.size() == 0)
        return;
    for(CameraContainer& cc : m_cameras){
        if(cc.name == camera){
            if(m_currentCamera && m_currentCamera->isInit())
                disconnect(m_currentCamera->controller, SIGNAL( processedImage(QImage) ), m_mw, SLOT( setImage(QImage) ));
            initCameraContainer(cc);
            m_currentCamera = &cc;
            loadCameraContainer(*m_currentCamera);
            connect(m_currentCamera->controller, SIGNAL( processedImage(QImage) ), m_mw, SLOT( setImage(QImage) ));
            printInfo("Selected camera: " + m_currentCamera->name + "(" + QString::number(m_currentCamera->id) + ")");
            return;
        }
    }
    printInfo("Error: no camera \"" + camera + "\" found");
}

void LiveCaptureWidget::startLivestreamCLicked(){
    if(m_currentCamera && m_currentCamera->controller){
        if(!m_currentCamera->controller->openStream()){
            printInfo("Error: Couldn't open the camera stream");
            return;
        }
        m_currentCamera->controller->startStream();
        loadCameraContainer(*m_currentCamera);
    }
}

void LiveCaptureWidget::stopLivestreamClicked(){
    if(m_currentCamera && m_currentCamera->controller){
        m_currentCamera->controller->stopStream();
        loadCameraContainer(*m_currentCamera);
    }
}

void LiveCaptureWidget::loadAreasClicked(){
    if(!m_currentCamera || !m_currentCamera->controller){
        printInfo("Error: No camera selected");
        return;
    }

    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Setting File (*.json)"));
    if(filename.isEmpty())
        return;

    if(!CURRENT_CAM_CTR){
        printInfo("Error: Couldn't initialize camera controller");
        return;
    }
    ImageScene& scene = m_mw->getImageScene();
    CURRENT_CAM_CTR->getSettings().hasParameters = JSONController::loadParameters(filename, CURRENT_CAM_CTR->getSettings().intrinsic, CURRENT_CAM_CTR->getSettings().distortion);
    if(CURRENT_CAM_CTR->getSettings().hasParameters){
        printInfo("Loaded parameters");
    }
    else{
        printInfo("No parameters loaded");
    }
    CURRENT_CAM_CTR->getSettings().m_rectList = JSONController::loadAreas(filename, scene.getImgWidth(), scene.getImgHeight());
    scene.setRectangles(*CURRENT_CAM_CTR->getSettings().m_rectList);
    printInfo("Loaded " + QString::number(CURRENT_CAM_CTR->getSettings().m_rectList->size()) + " areas");
    
    CURRENT_CAM_CTR->getSettings().resize = JSONController::loadSize(filename);
    if(CURRENT_CAM_CTR->getSettings().resize == -1)
        CURRENT_CAM_CTR->getSettings().resize = 48;
    printInfo("Loaded size " + QString::number(CURRENT_CAM_CTR->getSettings().resize) + "for resizing");
    
    CURRENT_CAM_CTR->getSettings().offset = JSONController::loadTimeOffset(filename);
    if(CURRENT_CAM_CTR->getSettings().offset <= 0)
        CURRENT_CAM_CTR->getSettings().offset = 1000;
    printInfo("Loaded offset with " + QString::number(CURRENT_CAM_CTR->getSettings().offset) + "msec");
    
    m_ui->lblLoadAreas->setText(filename);

    m_currentCamera->controller->refreshImage();
}

void LiveCaptureWidget::saveDirClicked(){
    QString dir = QFileDialog::getExistingDirectory ( this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dir != ""){
        m_ui->lblSaveDir->setText(dir);
        for(auto& camcon : m_cameras){
            camcon.controller->getSettings().saveDirectoryPath = dir;
        }
        printInfo("Save path set to: " + dir);
    }
}

void LiveCaptureWidget::startExtrClicked(){
    if(!m_currentCamera || !m_currentCamera->controller)
        return;
    if(m_currentCamera->controller->startExtracting(m_mw->getImageViewSize())){
        m_ui->btnStartExtr->setEnabled(false);
        m_ui->btnStopExtr->setEnabled(true);
        printInfo("Started extracting to:" + m_ui->lblSaveDir->text());
    }
    else{
        printInfo("Couldn't start extracting. Make sure you loaded areas, offset and a size");
    }
    
}

void LiveCaptureWidget::stopExtrClicked(){
    if(!m_currentCamera || !m_currentCamera->controller)
        return;
    if(m_currentCamera->controller->getSettings().isExtracting)
        printInfo("Stoped extracting");

    m_currentCamera->controller->stopExtracting();
    m_ui->btnStartExtr->setEnabled(true);
    m_ui->btnStopExtr->setEnabled(false);
    
}

void LiveCaptureWidget::startRecClicked(){
    if(!m_currentCamera || !m_currentCamera->controller)
        return;
    
    if(m_currentCamera->controller->startRecording()){
        m_ui->btnStartRec->setEnabled(false);
        m_ui->btnStopRec->setEnabled(true);
        printInfo("Started recording video: \n  " + m_currentCamera->controller->getSettings().recordingPath);
    }
    else{
        printInfo("Error: Couldn't start recording please try again and check your settings");
    }
}

void LiveCaptureWidget::stopRecClicked(){
    if(!m_currentCamera || !m_currentCamera->controller)
        return;

    printInfo("Stopped recording");
    m_currentCamera->controller->stopRecording();
}

void LiveCaptureWidget::initCameraContainer(CameraContainer& con){
    if(con.isInit())
        return;
    
    con.init();
    CameraSettings& settings = con.controller->getSettings();
    
    m_ui->lblLoadAreas->setText(settings.loadAreasPath = "/");
    m_ui->lblSaveDir->setText(settings.saveDirectoryPath = "/tmp");
    m_ui->btnStartLive->setEnabled(true);
    m_ui->btnStopLive->setEnabled(false);
    m_ui->btnStartRec->setEnabled(false);
    m_ui->btnStopRec->setEnabled(false);
    m_ui->btnStartExtr->setEnabled(false);
    m_ui->btnStopExtr->setEnabled(false);
    m_ui->btnLoadAreas->setEnabled(true);
    m_ui->btnSaveDir->setEnabled(true);

}

void LiveCaptureWidget::loadCameraContainer(CameraContainer& con){
    if(!con.isInit())
        return;
    
    con.controller->load();
    CameraSettings& settings = con.controller->getSettings();

    m_ui->lblLoadAreas->setText(settings.loadAreasPath);
    m_ui->lblSaveDir->setText(settings.saveDirectoryPath);
    if(!settings.isStreaming){
        m_ui->btnStartLive->setEnabled(true);
        m_ui->btnStopLive->setEnabled(false);
        m_ui->btnStartRec->setEnabled(false);
        m_ui->btnStopRec->setEnabled(false);
        m_ui->btnStartExtr->setEnabled(false);
        m_ui->btnStopExtr->setEnabled(false);
        m_ui->btnLoadAreas->setEnabled(true);
        m_ui->btnSaveDir->setEnabled(true);
    }
    else{
        m_ui->btnLoadAreas->setEnabled(false);
        m_ui->btnSaveDir->setEnabled(false);
        m_ui->btnStartLive->setEnabled(false);
        m_ui->btnStopLive->setEnabled(true);
        m_ui->btnStartRec->setEnabled(!settings.isRecording);
        m_ui->btnStopRec->setEnabled(settings.isRecording);
        m_ui->btnStartExtr->setEnabled(!settings.isExtracting);
        m_ui->btnStopExtr->setEnabled(settings.isExtracting);
    }
}

void LiveCaptureWidget::unloadCamerContainer(CameraContainer& con){
    if(!con.isInit())
        return;

    con.controller->unload();
    delete con.controller;
    con.controller = nullptr;
    
}
