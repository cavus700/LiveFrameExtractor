#include "header/VideoController.h"

VideoController::VideoController(QObject *parent) : QThread(parent)
{
    m_stop = true;
    m_initialised = false;
    m_parametersSet = false;
    m_saveMode = false;
}

VideoController::~VideoController()
{
    m_mutex.lock();
    m_stop = true;
    m_capture.release();
    m_condition.wakeOne();
    m_mutex.unlock();
    wait();
}

bool VideoController::loadVideo(std::string filename) {
    m_capture.open(filename);
    if (m_capture.isOpened())
    {
        m_frameRate = (int) m_capture.get(CV_CAP_PROP_FPS);
        m_initialised = true;
        return true;
    }
    else {
        m_initialised = false;
        return false;
    }
}

void VideoController::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            m_stop = false;
        }
        start(LowPriority);
    }
}

const QImage* VideoController::getImage(){
    if(m_initialised)
        return &m_img;
    else 
        return nullptr;
}

const QImage* VideoController::getNextFrame(){
    if(!m_initialised || !m_stop)
        return nullptr;

    if (!m_capture.read(m_frame)){
        return nullptr;
    }

    if(m_parametersSet)
        m_frame = ImageEditer::undistort(m_frame, m_parameters.intrinsic, m_parameters.distortion);

    if (m_frame.channels()== 3){
        cv::cvtColor(m_frame, m_RGBframe, CV_BGR2RGB);
        m_img = QImage((const unsigned char*)(m_RGBframe.data),
                            m_RGBframe.cols,m_RGBframe.rows,QImage::Format_RGB888);
    }
    else
    {
        m_img = QImage((const unsigned char*)(m_frame.data),
                                m_frame.cols,m_frame.rows,QImage::Format_Indexed8);
    }
    return &m_img;
}

void VideoController::run(){
    if(m_saveMode){
        saveImagesThread();
        m_saveMode = false;
        return;
    }
    int numFrames = static_cast<int>(m_capture.get(CAP_PROP_FRAME_COUNT));
    int frame = static_cast<int>(m_capture.get(CAP_PROP_POS_FRAMES));

    if(numFrames == frame)
        m_capture.set(CAP_PROP_POS_FRAMES , 0.0);

    int delay = (1000/m_frameRate);
    while(!m_stop){
        if (!m_capture.read(m_frame)){
            m_stop = true;
        }

        if(m_parametersSet)
            m_frame = ImageEditer::undistort(m_frame, m_parameters.intrinsic, m_parameters.distortion);

        if (m_frame.channels()== 3){
            cv::cvtColor(m_frame, m_RGBframe, CV_BGR2RGB);
            m_img = QImage((const unsigned char*)(m_RGBframe.data),
                                m_RGBframe.cols,m_RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            m_img = QImage((const unsigned char*)(m_frame.data),
                                    m_frame.cols,m_frame.rows,QImage::Format_Indexed8);
        }
        emit processedImage(m_img);
        emit videoProgress(m_capture.get(CAP_PROP_POS_FRAMES) / m_capture.get(CAP_PROP_FRAME_COUNT));
        this->msleep(delay);
    }
}

void VideoController::Stop()
{
    m_stop = true;
}

void VideoController::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

bool VideoController::isStopped() const{
    return this->m_stop;
}

void VideoController::setPosition(double pos){
    if(!m_initialised || !m_stop)
        return;
        
    if(pos < 0.0 || pos > 1.0)
        return;

    int numFrames = static_cast<int>(m_capture.get(CAP_PROP_FRAME_COUNT));
    int frame = static_cast<int>(numFrames * pos);

    if(!m_capture.set(CAP_PROP_POS_FRAMES , frame))
        return;

    if (!m_capture.read(m_frame)){
        return;
    }

    if(m_parametersSet)
        m_frame = ImageEditer::undistort(m_frame, m_parameters.intrinsic, m_parameters.distortion);

    if (m_frame.channels()== 3){
        cv::cvtColor(m_frame, m_RGBframe, CV_BGR2RGB);
        m_img = QImage((const unsigned char*)(m_RGBframe.data),
                            m_RGBframe.cols,m_RGBframe.rows,QImage::Format_RGB888);
    }
    else{
        m_img = QImage((const unsigned char*)(m_frame.data),
                                m_frame.cols,m_frame.rows,QImage::Format_Indexed8);
    }
    emit processedImage(m_img);
    emit videoProgress(m_capture.get(CAP_PROP_POS_FRAMES) / m_capture.get(CAP_PROP_FRAME_COUNT));
}

void VideoController::refreshImage(){
    if(m_initialised)
        emit processedImage(m_img);
}

void VideoController::setCameraParameters(CameraParameters params){
    m_parameters = params;
    m_parametersSet = true;
    if(m_initialised){
        const QImage* img = getNextFrame();
        if(img){
            emit processedImage(*img);
            emit videoProgress(m_capture.get(CAP_PROP_POS_FRAMES) / m_capture.get(CAP_PROP_FRAME_COUNT));
        }
    }
}

VideoController::CameraParameters* VideoController::getCameraParameters(){
    if(m_parametersSet){
        return &m_parameters;
    }
    else
        return nullptr;
}

void VideoController::removeCameraParameters(){
    m_parametersSet = false;
    if(m_initialised){
        const QImage* img = getNextFrame();
        if(img){
            emit processedImage(*img);
            emit videoProgress(m_capture.get(CAP_PROP_POS_FRAMES) / m_capture.get(CAP_PROP_FRAME_COUNT));
        }
    }
} 

void VideoController::saveImages(QList<QGraphicsRectItem*> rectList, QSize size, int offset, int resize, QString path){
    m_saveMode = true;
    m_rectList = rectList;
    m_offset = offset;
    m_resize = resize;
    m_size = size;
    m_path = path;
    start(LowPriority);
}

void VideoController::saveImagesThread(){
    if(!m_capture.set(CAP_PROP_POS_MSEC, 0.0)){
        emit savingFinished(false);
        return;
    }
    
    if(m_rectList.size() == 0){
        emit savingFinished(false);
        return;
    }

    int numFrames = static_cast<int>(m_capture.get(CAP_PROP_FRAME_COUNT));
    int frameRate = static_cast<int>(m_capture.get(CAP_PROP_FPS));
    int secLength = numFrames / frameRate;
    int posMSec = 0;
    int frame = 0;
    Mat currentFrame;
    QImage currentImage;
    QPixmap currentPixmap, croppedPixmap;
    QStringList savePaths;
    QString timestamp;
    QDir dir;

    //Initialize folders for each area
    for(int iRect = 0; iRect < m_rectList.size(); iRect++){
        QString path = m_path;
        if(m_rectList[iRect]->toolTip() == ""){
            path += "/Default";
            dir.mkdir(path);
            path += "/default-";
        }
        else{    
            path += "/" + m_rectList[iRect]->toolTip();
            dir.mkdir(path);
            path += "/" + m_rectList[iRect]->toolTip() + "-";
        }
        savePaths.push_back(path);
    }

    //Iterate over video and save images until finished
    while(m_saveMode && (posMSec / 1000) < secLength &&  m_capture.read(currentFrame)){
        
        if(m_parametersSet)
            currentFrame = ImageEditer::undistort(currentFrame, m_parameters.intrinsic, m_parameters.distortion);

        if (currentFrame.channels()== 3){
            cv::cvtColor(currentFrame, m_RGBframe, CV_BGR2RGB);
            currentImage = QImage((const unsigned char*)(m_RGBframe.data),
                                m_RGBframe.cols,m_RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            currentImage = QImage((const unsigned char*)(currentFrame.data),
                                    currentFrame.cols,currentFrame.rows,QImage::Format_Indexed8);

            currentImage = currentImage.convertToFormat(QImage::Format_RGB888);
        }
        
        currentPixmap = QPixmap::fromImage(currentImage).scaled(m_size,
                                       Qt::KeepAspectRatio, Qt::FastTransformation);

        //Save a picture for each area
        for(int iRect = 0; iRect < m_rectList.size(); iRect++){
            croppedPixmap = currentPixmap.copy(m_rectList[iRect]->rect().toRect());
            croppedPixmap = ImageEditer::applyPaddingAndScale(croppedPixmap, m_resize);
            QDateTime time = QDateTime::currentDateTimeUtc();
            timestamp = QString::number(time.time().hour()) + ":" + QString::number(time.time().minute()) + ":" + QString::number(time.time().second()) + ":" + QString::number(time.time().msec());
            croppedPixmap.save(savePaths[iRect] + timestamp + ".png");
        }

        frame = static_cast<int>(m_capture.get(CAP_PROP_POS_FRAMES));
        emit savingProgress((frame * 100) / numFrames);

        posMSec += m_offset;
        m_capture.set(CAP_PROP_POS_MSEC, posMSec);
    }
    emit savingFinished(true);
    emit savingProgress(100);
}
