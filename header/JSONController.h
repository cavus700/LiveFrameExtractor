#ifndef JSONCONTROLLER_H
#define JSONCONTROLLER_H

#define OPACITY 0.4
#define FILE_NAME "/setting.json"

#include <QGraphicsRectItem>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include <QBrush>
#include <QPen>
#include "header/VideoController.h"

class JSONController{
    
public:
    static void saveAreas(QList<QGraphicsRectItem*>& rectList, int imgWidth, int imgHeight, QString path);
    static void saveTimeOffset(int offset, QString path);
    static void saveSize(int size, QString path);
    static void saveParameters(VideoController::CameraParameters& params , QString path);
    static QList<QGraphicsRectItem*>* loadAreas(QString path, int imgWidth, int imgHeight);
    static int loadTimeOffset(QString path);
    static int loadSize(QString path);
    static bool loadParameters(QString path, VideoController::CameraParameters&);
    static bool loadParameters(QString path, Mat& intrinsic, Mat& distortion);

private:
    static QJsonDocument loadDocument(QString path);
    static void saveDocument(QJsonDocument doc, QString path);
};

#endif