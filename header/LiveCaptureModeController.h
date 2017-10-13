#ifndef LIVECAPTUREMODECONTROLLER_H
#define LIVECAPTUREMODECONTROLLER_H
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "header/LiveCameraController.h"
#include "header/JSONController.h"

#define CURRENT_CAM_CTR (m_currentCamera->controller)
//Forward declarations
namespace Ui {
    class LiveCaptureWidget;
}

class MainWindow;

class LiveCaptureWidget : public QWidget
{
    Q_OBJECT

private:
struct CameraContainer{
    CameraContainer(QString name, int id) : name(name), id(id) {  }
    ~CameraContainer(){ 
        if(controller){
            delete controller;
        } 
    } 
    QString name;
    int id;
    LiveCameraController* controller = nullptr;
    bool isInit(){ return controller != nullptr;}
    void init(){ if(!controller) controller = new LiveCameraController(id); controller->load(); }
};

public:
    explicit LiveCaptureWidget(MainWindow *mw, QWidget *parent = 0);
    virtual ~LiveCaptureWidget();
  
private:
    MainWindow *m_mw;
    Ui::LiveCaptureWidget *m_ui;
    CameraContainer* m_currentCamera;
    QList<CameraContainer> m_cameras;

    void initSIGNALSandSLOTS();
    void printInfo(QString);
    void initCameraContainer(CameraContainer& con);
    //Loads current configurations and sets GUI buttons
    void loadCameraContainer(CameraContainer& con);
    void unloadCamerContainer(CameraContainer& con);

private slots:
    void handleCameraChanged(QString camera);
    void startLivestreamCLicked();
    void stopLivestreamClicked();
    void loadAreasClicked();
    void saveDirClicked();
    void startExtrClicked();
    void stopExtrClicked();
    void startRecClicked();
    void stopRecClicked();
};

#endif