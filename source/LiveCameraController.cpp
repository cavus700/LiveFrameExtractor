#include "header/LiveCameraController.h"
#include "header/ImageEditer.h"

LiveCameraController::LiveCameraController(int id) :
    m_settings(id),
    m_capture(nullptr),
    m_vidWriter(nullptr),
    m_timerExtr(nullptr)
{
    initSettings();
}

LiveCameraController::~LiveCameraController(){
    if(m_settings.isStreaming){
        stopStream();
    }
    this->wait(200);
    if(m_capture)
        delete m_capture;
}

void LiveCameraController::initSettings(){
    m_settings.hasParameters = false;
    m_settings.isStreaming = false;
    m_settings.isRecording = false;  
    m_settings.isExtracting = false;
    m_settings.resize = -1;
    m_settings.offset = -1;
    m_settings.saveDirectoryPath = "/tmp";
}

void LiveCameraController::refreshImage(){
    processedImage(m_img);
}

void LiveCameraController::load(){
    
}

void LiveCameraController::unload(){
    if(m_settings.isStreaming){
        stopStream();
    }
}

bool LiveCameraController::openStream(){
    if(m_capture && m_capture->isOpened())
        return true;
    
    m_capture = new VideoCapture(m_settings.cameraId);
    if(m_capture->isOpened()){
        return true;    
    }
    else{
        m_capture = nullptr;
        return false;
    }
}

void LiveCameraController::run(){    
    while(m_settings.isStreaming){
        if (!m_capture || !m_capture->read(m_frame)){
            m_settings.isStreaming = true;
        }
        if(m_settings.hasParameters)
            m_frame = ImageEditer::undistort(m_frame, m_settings.intrinsic, m_settings.distortion);

        if(m_settings.isRecording)
            recordVideo(m_frame);

        if (m_frame.channels()== 3){
            cv::cvtColor(m_frame, m_RGBframe, CV_BGR2RGB);
            m_img = QImage((const unsigned char*)(m_RGBframe.data),
                                m_RGBframe.cols,m_RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            m_img = QImage((const unsigned char*)(m_frame.data),
                                    m_frame.cols,m_frame.rows,QImage::Format_Indexed8);
            
            m_img = m_img.convertToFormat(QImage::Format_RGB888);
        }

        if(m_settings.isExtracting){
            extractImage(m_img);
        }

        emit processedImage(m_img);
    }
}

void LiveCameraController::extractImage(QImage& img){
    if(m_timerExtr->elapsed() < m_settings.offset )
        return;

    QPixmap croppedPixmap;
    QPixmap currentPixmap = QPixmap::fromImage(img).scaled(m_settings.imgSize,
                                    Qt::KeepAspectRatio, Qt::FastTransformation);

    //Save a picture for each area
    for(int iRect = 0; iRect < m_settings.m_rectList->size(); iRect++){
        croppedPixmap = currentPixmap.copy(m_settings.m_rectList[0][iRect]->rect().toRect());
        croppedPixmap = ImageEditer::applyPaddingAndScale(croppedPixmap, m_settings.resize);
        QDateTime time = QDateTime::currentDateTimeUtc();
        QString timestamp = QString::number(time.time().hour()) + ":" + QString::number(time.time().minute()) + ":" + QString::number(time.time().second()) + ":" + QString::number(time.time().msec());
        croppedPixmap.save(m_settings.savePaths[iRect] + timestamp + ".png");
    }
    m_timerExtr->restart();
}

void LiveCameraController::recordVideo(Mat& frame){
    if(m_vidWriter && m_vidWriter->isOpened())
        *m_vidWriter << frame;
}

void LiveCameraController::startStream(){
    if(!isRunning()){
        if(!m_settings.isStreaming){
            m_settings.isStreaming = true;
            this->start(LowPriority);
        }
    }
}

void LiveCameraController::stopStream(){
    m_settings.isStreaming = false;
    if(m_settings.isExtracting)
        stopExtracting();
    if(m_settings.isRecording)
        stopRecording();
    this->wait();
    if(m_capture)
        delete m_capture;
    m_capture = nullptr;
    if(m_timerExtr){
        delete m_timerExtr;
        m_timerExtr = nullptr;
    }
}

bool LiveCameraController::startRecording(){
    if(!m_settings.isStreaming || !m_capture)
        return false;
    
    //Find name for new video file
    QString file = m_settings.saveDirectoryPath + "/video" + QString::number(m_settings.cameraId);
    int num = 0;
    QFileInfo check_file(file + "_" + QString::number(num) + ".mp4");

    while(check_file.exists() && check_file.isFile()){
        num++;
        
        if(num > 10000)
            return false;
    }
    file += "_" + QString::number(num) + ".avi";
      
    // Acquire input size   
    Size S = Size((int) m_capture->get(CV_CAP_PROP_FRAME_WIDTH),    
                  (int) m_capture->get(CV_CAP_PROP_FRAME_HEIGHT));

    //Open video writer
    m_vidWriter = new VideoWriter();
    m_vidWriter->open(file.toUtf8().constData(), CV_FOURCC('M','J','P','G'), m_capture->get(CV_CAP_PROP_FPS), S, true);

    if (!m_vidWriter->isOpened())
    {
        return false;
    }

    return m_settings.isRecording = true;
}

void LiveCameraController::stopRecording(){
    m_settings.isRecording = false;
    if(m_vidWriter){
        m_vidWriter->release();
        delete m_vidWriter;
        m_vidWriter = nullptr;
    }
}

bool LiveCameraController::startExtracting(QSize size){
    if(!m_settings.isStreaming)
        return false;

    if(!m_settings.m_rectList || m_settings.m_rectList->size() <= 0 || m_settings.resize <= 0 || m_settings.offset <= 0)
        return false;

    QDir dir;
    m_settings.savePaths.clear();
    m_settings.imgSize = size;
    //Initialize folders for each area
    for(int iRect = 0; iRect < m_settings.m_rectList->size(); iRect++){
        QString path = m_settings.saveDirectoryPath;
        if(m_settings.m_rectList[0][iRect]->toolTip() == ""){
            path += "/Default";
            dir.mkdir(path);
            path += "/default-";
        }
        else{    
            path += "/" + m_settings.m_rectList[0][iRect]->toolTip();
            dir.mkdir(path);
            path += "/" + m_settings.m_rectList[0][iRect]->toolTip() + "-";
        }
        m_settings.savePaths.push_back(path);
    }
    m_timerExtr = new QTime();
    m_timerExtr->start();
    return m_settings.isExtracting = true;
    
}

void LiveCameraController::stopExtracting(){
    m_settings.isExtracting = false;
    if(m_timerExtr){
        delete m_timerExtr;
        m_timerExtr = nullptr;
    }
}