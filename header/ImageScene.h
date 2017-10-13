#ifndef IMAGESCENE_H
#define IMAGESCENE_H

#define UNUSED(x) (void)(x)
#define OPACITY 0.4

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QtAlgorithms>

class ImageScene : public QGraphicsScene {
    Q_OBJECT

public:
    ImageScene(QObject * parent = 0);
    ~ImageScene();

    void addPixmap(const QPixmap & pixmap);
    bool addRectangle(int width = 50, int height = 50);
    QString removeRectangle();
    QString resizeRectangle(int width, int height);
    void renameRectangle(QString);
    void setEnableDragMode(bool enable);
    void clear();

    void setRectangles(QList<QGraphicsRectItem*>& rectList);
    QList<QGraphicsRectItem*>& getRectangles(){ return m_rects;}
    int getImgWidth() { return m_imgWidth; }
    int getImgHeight() { return m_imgHeight; }
    
private:
    int m_imgWidth;
    int m_imgHeight;
    int m_oldXMouse;
    int m_oldYMouse;
    bool m_dragMode;
    QList<QGraphicsRectItem*> m_rects;
    QGraphicsRectItem* m_selectedRect;
    QGraphicsPixmapItem* m_pixmap;

    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);

    QGraphicsRectItem* selectRectangle(int x, int y);
    void moveRectangle(int xNew, int yNew);
    bool checkResize(int width, int height);
    void handleResize(int width, int height);
    
signals:
    void mouseImagePosition(int x, int y);
    void selectionChanged(const QGraphicsRectItem&);
};

#endif 