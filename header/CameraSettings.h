#ifndef CAMERASETTINGS_H
#define CAMERASETTINGS_H

#include <opencv2/core/core.hpp>
#include <QString>
#include <QList>
#include <QGraphicsRectItem>
#include <QSize>

using namespace cv;

class CameraSettings{
public:    
    CameraSettings(int id) : cameraId(id){ 
    }

    QString loadAreasPath;
    QString saveDirectoryPath;
    QStringList savePaths;
    QString recordingPath;
    bool isStreaming;
    bool isRecording;
    bool isExtracting;
    bool hasParameters;
    Mat intrinsic;
    Mat distortion;
    int cameraId;
    int framerate;
    int resize;
    int offset;
    QSize imgSize;
    QList<QGraphicsRectItem*>* m_rectList = nullptr;    
};

#endif //CAMERASETTINGS_H
