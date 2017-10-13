#ifndef IMAGEEDITER_H
#define IMAGEEDITER_H

#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class ImageEditer{

public:
    static QPixmap applyPaddingAndScale(QPixmap& pixmap, int size){
        QImage image = pixmap.toImage();
        QImage padded;
        int pxWidth = image.width();
        int pxHeight = image.height();
        
        if(pxWidth > pxHeight){
            padded = QImage(pxWidth, pxHeight + (pxWidth - pxHeight), image.format());
            padded.fill(Qt::black);
            QPainter painter{&padded};
            painter.drawImage(QPoint(0, (pxWidth - pxHeight) / 2), image);
        }
        else{
            padded = QImage(pxWidth + (pxHeight - pxWidth), pxHeight, image.format());
            padded.fill(Qt::black);
            QPainter painter{&padded};
            painter.drawImage(QPoint((pxHeight - pxWidth) / 2, 0), image);
        }
        
        QPixmap resultMap = QPixmap::fromImage(padded);
        return resultMap.scaled(size, size);
    }

    static Mat undistort(Mat frame, Mat intrinsic, Mat distortion){
        Mat undistortFrame;
        cv::undistort(frame, undistortFrame, intrinsic, distortion);
        return undistortFrame;
    }

};

#endif