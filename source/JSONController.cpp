#include "header/JSONController.h"

void JSONController::saveAreas(QList<QGraphicsRectItem*>& rectList, int imgWidth, int imgHeight, QString path){
    QJsonDocument jsonDoc = loadDocument(path + QString(FILE_NAME));
    QJsonArray jsonAreas;

    for(auto rect : rectList){
        QRectF rectSize = rect->rect();
        QJsonObject jsonRect;

        jsonRect["percXLeft"] = static_cast<double>(rectSize.x()) / static_cast<double>(imgWidth);
        jsonRect["percXRight"] = (imgWidth - static_cast<double>(rectSize.x() + rectSize.width())) / static_cast<double>(imgWidth);
        jsonRect["percYTop"] = static_cast<double>(rectSize.y()) / static_cast<double>(imgHeight);
        jsonRect["percYBottom"] = (imgHeight - static_cast<double>(rectSize.y() + rectSize.height())) / static_cast<double>(imgHeight);
        jsonRect["rectId"] = rect->toolTip();

        jsonAreas.append(jsonRect);
    }
    QJsonObject json = jsonDoc.object();
    json.insert("areas", jsonAreas);
    jsonDoc.setObject(json);    

    saveDocument(QJsonDocument(json), path + QString(FILE_NAME));
}

// void JSONController::saveFilename(QString name, QString path){
//     QJsonDocument jsonDoc = loadDocument(path + QString(FILE_NAME));

//     QJsonObject json = jsonDoc.object();
//     json.insert("filename", name);
//     jsonDoc.setObject(json);    

//     saveDocument(QJsonDocument(json), path += QString(FILE_NAME));
// }

void JSONController::saveTimeOffset(int offset, QString path){
    QJsonDocument jsonDoc = loadDocument(path + QString(FILE_NAME));

    QJsonObject json = jsonDoc.object();
    json.insert("offset", offset);
    jsonDoc.setObject(json);    

    saveDocument(QJsonDocument(json), path + QString(FILE_NAME));
}

void JSONController::saveSize(int size, QString path){
    QJsonDocument jsonDoc = loadDocument(path + QString(FILE_NAME));

    QJsonObject json = jsonDoc.object();
    json.insert("size", size);
    jsonDoc.setObject(json);    

    saveDocument(QJsonDocument(json), path + QString(FILE_NAME));
}

void JSONController::saveParameters(VideoController::CameraParameters& params , QString path){
    QJsonDocument jsonDoc = loadDocument(path + QString(FILE_NAME));

    QJsonObject json = jsonDoc.object(), jsonParam;
    QJsonArray jsonMatCamera, jsonMatDistortion;
    for(int iRow = 0; iRow < 3; iRow++){
        for(int iCol = 0; iCol < 3; iCol++){
            jsonMatCamera.append(QString::number(params.intrinsic.ptr<float>(iRow)[iCol]));   
        }  
    }
    for(int iCol = 0; iCol < 5; iCol++){
        jsonMatDistortion.append(QString::number(params.distortion.ptr<float>(0)[iCol]));
    }
    jsonParam["intrinsic"] = jsonMatCamera;
    jsonParam["distortion"] = jsonMatDistortion;
    json.insert("parameters", jsonParam);
    jsonDoc.setObject(json);    

    saveDocument(QJsonDocument(json), path + QString(FILE_NAME));
}

QList<QGraphicsRectItem*>* JSONController::loadAreas(QString path, int imgWidth, int imgHeight){
    QJsonDocument jsonDoc = loadDocument(path);

    QJsonArray areas = jsonDoc.object()["areas"].toArray(); 

    QList<QGraphicsRectItem*>* resultRects = new QList<QGraphicsRectItem*>();
    double percXLeft, percXRight, percYTop, percYBottom;

    for (int iArea = 0; iArea < areas.size(); iArea++) {
        QJsonObject area = areas[iArea].toObject();
        if(area["percXLeft"] == QJsonValue::Undefined)
            continue;
        if(area["percXRight"] == QJsonValue::Undefined)
            continue;
        if(area["percYTop"] == QJsonValue::Undefined)
            continue;
        if(area["percYBottom"] == QJsonValue::Undefined)
            continue;
        
        percXLeft = area["percXLeft"].toDouble();
        percXRight = area["percXRight"].toDouble();
        percYTop = area["percYTop"].toDouble();
        percYBottom = area["percYBottom"].toDouble();

        QRectF rectSize;
        rectSize.setX(percXLeft * imgWidth);
        rectSize.setY(percYTop * imgHeight);
        rectSize.setWidth((1.0 - (percXLeft + percXRight)) * imgWidth);
        rectSize.setHeight((1.0 - (percYTop + percYBottom)) * imgHeight);

        QGraphicsRectItem* newRect = new QGraphicsRectItem(rectSize);
        newRect->setRect(rectSize);
        if(area["rectId"] != QJsonValue::Undefined)
            newRect->setToolTip(area["rectId"].toString());
        newRect->setOpacity(OPACITY);
        newRect->setBrush(QBrush(Qt::blue));
        QPen outlinePen(Qt::black); 
        outlinePen.setWidth(2); 
        newRect->setPen(outlinePen);
        resultRects->push_back(newRect);
    }
    return resultRects;
}

int JSONController::loadTimeOffset(QString path){
    QJsonDocument jsonDoc = loadDocument(path);
    QJsonObject json = jsonDoc.object();
    if(json["offset"] == QJsonValue::Undefined){
        return -1;
    } 
    else{
        return json["offset"].toInt();
    }
}

int JSONController::loadSize(QString path){
    QJsonDocument jsonDoc = loadDocument(path);
    QJsonObject json = jsonDoc.object();
    if(json["size"] == QJsonValue::Undefined){
        return -1;
    } 
    else{
        return json["size"].toInt();
    }
}

bool JSONController::loadParameters(QString path, VideoController::CameraParameters& params){
    return loadParameters(path, params.intrinsic, params.distortion);
}

bool JSONController::loadParameters(QString path, Mat& intrinsic, Mat& distortion){
    QJsonDocument jsonDoc = loadDocument(path);
    QJsonObject json = jsonDoc.object();
    if(json["parameters"] == QJsonValue::Undefined)
        return false;
    
    QJsonObject jsonParams = json["parameters"].toObject();

    if(jsonParams["intrinsic"] == QJsonValue::Undefined)
        return false;
    else{
        QJsonArray arr = jsonParams["intrinsic"].toArray();
        if(arr.size() != 9)
            return false;
        
        cv::Mat mat(3, 3, CV_32FC1);
        for (int iCoeff = 0; iCoeff < arr.size(); iCoeff++) {
            mat.ptr<float>(iCoeff / 3)[iCoeff % 3] = static_cast<float>(arr[iCoeff].toVariant().toFloat());
        }
        intrinsic = mat;
    }

    if(jsonParams["distortion"] == QJsonValue::Undefined)
        return false;
    else{
        QJsonArray arr = jsonParams["distortion"].toArray();
        if(arr.size() != 5)
            return false;
        
        cv::Mat mat(1, 5, CV_32FC1);
        for (int iCoeff = 0; iCoeff < arr.size(); iCoeff++) {
            mat.ptr<float>(0)[iCoeff] = static_cast<float>(arr[iCoeff].toVariant().toFloat());
        }
        distortion = mat;
    }
    return true;
}

QJsonDocument JSONController::loadDocument(QString path){
    QFile jsonFile(path);
    jsonFile.open(QFile::ReadOnly);
    return QJsonDocument().fromJson(jsonFile.readAll());
}

void JSONController::saveDocument(QJsonDocument doc, QString path){
    QFile jsonFile(path);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(doc.toJson());
}
