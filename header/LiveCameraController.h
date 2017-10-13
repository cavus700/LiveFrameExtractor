#ifndef LIVECAMERACONTROLLER_H
#define LIVECAMERACONTROLLER_H

#include "header/CameraSettings.h"
#include "header/ImageEditer.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <QThread>
#include <QImage>
#include <QDateTime>
#include <QDir>
#include <QTime>
#include <QFileInfo>

class LiveCameraController : public QThread{
    Q_OBJECT

public:
    LiveCameraController(int id);
    ~LiveCameraController();

    void load();
    void unload();
    void refreshImage();
    bool openStream();
    void startStream();
    void stopStream();
    bool startRecording();
    void stopRecording();
    bool startExtracting(QSize size);
    void stopExtracting();

    CameraSettings& getSettings(){ return m_settings; }
    
signals:
    void processedImage(const QImage &image);

private:
    CameraSettings m_settings;
    VideoCapture* m_capture;
    VideoWriter* m_vidWriter;
    Mat m_frame;
    Mat m_RGBframe;
    QImage m_img;
    QTime* m_timerExtr;

    void initSettings();   
    void run();
    void extractImage(QImage& img);
    void recordVideo(Mat& frame);
};

#endif //LIVECAMERACONTROLLER_H