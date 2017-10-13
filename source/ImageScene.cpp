#include "header/ImageScene.h"
#include <iostream>

ImageScene::ImageScene(QObject * parent) 
    : QGraphicsScene(parent), 
      m_imgWidth(-1), 
      m_imgHeight(-1),
      m_dragMode(true),
      m_selectedRect(nullptr),
      m_pixmap(nullptr)
{
        
}

ImageScene::~ImageScene(){
    m_rects.clear();

    for(QGraphicsItem* item : this->items()){
        this->removeItem(item);
    }
}

void ImageScene::clearRect(){
    if(m_selectedRect){
        m_selectedRect->setBrush(QBrush(Qt::blue));
        m_selectedRect = nullptr;
    }
}

void ImageScene::clear(){
    qDeleteAll( this->items() );
    m_rects.clear();
    m_pixmap = nullptr;
}

void ImageScene::setRectangles(QList<QGraphicsRectItem*>& rectList){ 
    for(QGraphicsItem* item : this->items()){
        if(dynamic_cast<QGraphicsRectItem*>(item)){
            this->removeItem(item);
        }
    }
    
    m_rects.clear(); 
    m_rects = rectList; 

    for(QGraphicsRectItem* rect : m_rects){
        this->addItem(rect);
    }
    
}

bool ImageScene::addRectangle(int width, int height){
    if(width <= 10 || height <= 10)
        return false;
    if(width >= m_imgWidth || height >= m_imgHeight)
        return false;
    if(m_rects.size() >= 50)
        return false;

    QBrush blueBrush(Qt::blue); 
    QPen outlinePen(Qt::black); 
    outlinePen.setWidth(2); 
    QGraphicsRectItem* rectangle = this->addRect(0, 0, width, height, outlinePen, blueBrush);
    rectangle->setOpacity(OPACITY);
    m_rects.push_back(rectangle);

    return true;    
}

QString ImageScene::removeRectangle(){
    if(!m_selectedRect){
        return QString("Error: No area selected");
    }

    this->removeItem(m_selectedRect);
    m_rects.removeOne(m_selectedRect);
    QString name = m_selectedRect->toolTip();
    delete m_selectedRect;
    m_selectedRect = nullptr;
    return "Area (\"" + name  + "\") successfull removed!";
}

QString ImageScene::resizeRectangle(int width, int height){
    if(!m_selectedRect)
        return QString("Error: No area selected");
    
    if(width < 10 || height < 10)
        return QString("Error: Minimum size is 10px");

    if(m_selectedRect->rect().x() + width <= m_imgWidth){
        if(m_selectedRect->rect().y() + height <= m_imgHeight){
            m_selectedRect->setRect(QRectF(m_selectedRect->rect().x(), m_selectedRect->rect().y(), width, height));
            return QString("Area successfull resized!");
        }
    }
    return QString("Error: Area size is out of bounds");
}

void ImageScene::renameRectangle(QString name){
    if(m_selectedRect){
        m_selectedRect->setToolTip(name);
    }
}

void ImageScene::setEnableDragMode(bool enable){
    if(!enable){
        m_selectedRect = nullptr;
    }
    m_dragMode = enable;
}

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(!m_dragMode)
        return;
    if(m_selectedRect){
        m_selectedRect->setBrush(QBrush(Qt::blue));
        m_selectedRect = nullptr;
    }

    QGraphicsRectItem* rect = selectRectangle(event->scenePos().x(), event->scenePos().y());

    if(!rect)
        return;
    
    m_selectedRect = rect; 
    emit selectionChanged(*m_selectedRect);
    m_selectedRect->setBrush(QBrush(Qt::red));
    m_oldXMouse = event->scenePos().x();
    m_oldYMouse = event->scenePos().y();
}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    int x = event->scenePos().x();
    int y = event->scenePos().y();
    
    if(x < 0 || x >= m_imgWidth){
        if(y < 0 || y >= m_imgHeight){
            moveRectangle(-1, -1);
            return;
        }
        moveRectangle(-1, y);
        return;
    }
    else{
        if(y < 0 || y >= m_imgHeight){
            moveRectangle(x, -1);
            return;
        }
        moveRectangle(x, y);
        return;
    }
}

QGraphicsRectItem* ImageScene::selectRectangle(int x, int y){
    int xRect = 0, yRect = 0;
    int widthRect = 0, heightRect = 0;

    for(auto rectIter = m_rects.crbegin(); rectIter != m_rects.crend(); rectIter++){
        xRect = (*rectIter)->rect().x();
        yRect = (*rectIter)->rect().y();
        widthRect = (*rectIter)->rect().width();
        heightRect = (*rectIter)->rect().height();

        if(x >= xRect && x < (xRect + widthRect) && y >= yRect && y < (yRect + heightRect)){
            return *rectIter;
        }
    }

    return nullptr;
}

void ImageScene::moveRectangle(int xNew, int yNew){
    if(xNew < 0 && yNew < 0)
        return;
    if(!m_selectedRect)
        return;
    
    QRectF rect = m_selectedRect->rect();
    int xMove = rect.x(), yMove = rect.y();

    if(xNew >= 0){
        int xDelta = xNew - m_oldXMouse ;

        if((rect.x() + xDelta) >= 0 && (rect.x() + rect.width() + xDelta) < m_imgWidth ){
            xMove += xDelta;
        }
    }
    
    if(yNew >= 0){
        int yDelta = yNew - m_oldYMouse;

        if((rect.y() + yDelta) >= 0 && (rect.y() + rect.height() + yDelta) < m_imgHeight ){
            yMove += yDelta;
        }
    }

    m_selectedRect->setRect(QRectF(xMove, yMove, rect.width(), rect.height()));

    m_oldXMouse = xNew;
    m_oldYMouse = yNew;
}

void ImageScene::addPixmap(const QPixmap & pixmap){
    if(m_selectedRect){
        m_selectedRect->setBrush(QBrush(Qt::blue));
        m_selectedRect = nullptr;
    }
    
    if(m_pixmap == nullptr){
        m_pixmap = QGraphicsScene::addPixmap(pixmap);
    }
    else{
        m_pixmap->setPixmap(pixmap);
    }

    checkResize(pixmap.width(), pixmap.height());

    m_imgWidth = pixmap.width();
    m_imgHeight = pixmap.height();
}

bool ImageScene::checkResize(int width, int height){
    if(m_imgWidth == -1 || m_imgHeight == -1)
        return false;
    if(m_imgWidth == width && m_imgHeight == height)
        return false;
    
    handleResize(width, height);
    return true;
}

void ImageScene::handleResize(int width, int height){
    if(m_selectedRect){
        m_selectedRect->setBrush(QBrush(Qt::blue));
        m_selectedRect = nullptr;
    }

    double percXLeft, percXRight, percYTop, percYBottom;

    for(QGraphicsItem* item : this->items()){
        if(!dynamic_cast<QGraphicsRectItem*>(item))
            continue;
        
        QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(item);
        QRectF rectSize = rect->rect();
        
        percXLeft = static_cast<double>(rectSize.x()) / static_cast<double>(m_imgWidth);
        percXRight = (m_imgWidth - static_cast<double>(rectSize.x() + rectSize.width())) / static_cast<double>(m_imgWidth);
        percYTop = static_cast<double>(rectSize.y()) / static_cast<double>(m_imgHeight);
        percYBottom = (m_imgHeight - static_cast<double>(rectSize.y() + rectSize.height())) / static_cast<double>(m_imgHeight);

        rectSize.setX(percXLeft * width);
        rectSize.setY(percYTop * height);
        rectSize.setWidth((1.0 - (percXLeft + percXRight)) * width);
        rectSize.setHeight((1.0 - (percYTop + percYBottom)) * height);

        rect->setRect(rectSize);
    } 
}