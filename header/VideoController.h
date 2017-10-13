#ifndef VIDEO_H
#define VIDEO_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QString>
#include <QList>
#include <QGraphicsRectItem>
#include <QWaitCondition>
#include <QDateTime>
#include <QDir>
#include <QPainter>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "header/ImageEditer.h"

using namespace cv;

class VideoController : public QThread
{    
    Q_OBJECT

public:
    struct CameraParameters{
        Mat intrinsic;
        Mat distortion;
    };

private:
    bool m_saveMode;
    bool m_stop;
    bool m_initialised;
    bool m_parametersSet;
    QMutex m_mutex;
    QWaitCondition m_condition;
    Mat m_frame;
    int m_frameRate;
    VideoCapture m_capture;
    Mat m_RGBframe;
    CameraParameters m_parameters;
    QImage m_img;

    //For image saving thread
    QList<QGraphicsRectItem*> m_rectList;
    int m_offset, m_resize;
    QSize m_size;
    QString m_path;   

    void saveImagesThread();
signals:
    //Signal to output frame to be displayed
    void processedImage(const QImage &image);
    void videoProgress(const double pos);
    void savingProgress(int prog);
    void savingFinished(bool success);

protected:
    void run();
    void msleep(int ms);

public:
    //Constructor
    VideoController(QObject *parent = 0);
    //Destructor
    ~VideoController();
    //Load a video from memory
    bool loadVideo(std::string filename);
    //Play the video
    void Play();
    //Stop the video
    void Stop();
    //Stops saving thread
    void stopSaving() { m_saveMode = false; }
    //check if the player has been stopped
    bool isStopped() const;
    //Gets the next frame from the video
    const QImage* getNextFrame();
    //Gets the current image
    const QImage* getImage();
    //Sets video to a position between 0 and 1
    void setPosition(double pos);
    //Emits the actual image again
    void refreshImage();
    //Sets camera and distortion coefficients
    void setCameraParameters(CameraParameters params);
    //Gets camera and distortion coefficients
    CameraParameters* getCameraParameters();
    //Removes camera and distortion coefficients
    void removeCameraParameters(); 
    //Saves marked regions from images
    void saveImages(QList<QGraphicsRectItem*> rectList, QSize size, int offset, int resize, QString path);
};
#endif // VIDEO_H