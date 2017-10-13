#include "header/MainWindow.h"
#include "header/LiveCaptureModeController.h"
#include "header/VideoModeController.h"
#include "header/ImageScene.h"
#include "ui_LiveFrameExtractorUI.h"
#include <iostream>
#include <QGraphicsItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    
    m_ui->setupUi(this);

    m_imageView = new ImageScene(this);
    m_ui->graphicsView->setScene(m_imageView);

    connect(m_ui->btnV, SIGNAL( clicked() ), this, SLOT( onRadioButtonClicked() ));
    connect(m_ui->btnLC, SIGNAL( clicked() ), this, SLOT( onRadioButtonClicked() ));
}

MainWindow::~MainWindow()
{
    delete m_ui;
    if(m_liveCaptureWidget)
        delete m_liveCaptureWidget;
    if(m_videoWidget)
        delete m_videoWidget;
}

ImageScene& MainWindow::getImageScene(){
    return *m_imageView;
}

QSize MainWindow::getImageViewSize(){
    return m_ui->graphicsView->size();
}

void MainWindow::setImage(QImage img){
    if (!img.isNull())
    {   
        m_imageView->addPixmap(QPixmap::fromImage(img).scaled(m_ui->graphicsView->size(),
                                       Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    UNUSED(event);
    if(m_videoWidget)
        m_videoWidget->handleResize();
}

void MainWindow::onRadioButtonClicked(){
    QWidget* widget = nullptr;
    
    auto item = m_ui->gridMain->itemAtPosition(2, 0);
    if(item)
        widget = item->widget();
    else{
        item = m_ui->gridMain->itemAtPosition(0, 5);
        if(item)
            widget = item->widget();       
    }
    
    if(m_ui->btnLC->isChecked()) {
        if(widget)
            m_ui->gridMain->removeWidget(widget);
        deleteWidget();
        
        m_liveCaptureWidget = new LiveCaptureWidget(this);
        m_ui->gridMain->addWidget(m_liveCaptureWidget, 2, 0, 1, 5); 
    }
    else{
        if(widget)
            m_ui->gridMain->removeWidget(widget);
        deleteWidget();

        m_videoWidget = new VideoWidget(this);
        m_ui->gridMain->addWidget(m_videoWidget, 0, 5, 2, 1); 
    }
}

void MainWindow::deleteWidget(){
    if(m_liveCaptureWidget){
        m_liveCaptureWidget->deleteLater();
        m_liveCaptureWidget = nullptr;
    }
    if(m_videoWidget){
        m_videoWidget->deleteLater();
        m_videoWidget = nullptr;
    }
    m_imageView->clear(); 
}