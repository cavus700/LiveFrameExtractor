#ifndef VIDEOMODECONTROLLER_H
#define VIDEOMODECONTROLLER_H
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsRectItem>

//Forward declarations
namespace Ui {
    class VideoWidget;
}
class MainWindow;
class VideoController;
class ImageScene;

class VideoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit VideoWidget(MainWindow *mw, QWidget *parent = 0);
    virtual ~VideoWidget();
  
    void handleResize();
    
private:
    MainWindow *m_mw;
    Ui::VideoWidget *m_ui;
    VideoController *m_vidController = nullptr;

    void initSIGNALSandSLOTS();
    void printInfo(QString);
    void enableButtons();
    void disableButtons();
    
private slots:
    void sliderUpdate(double val);
    void savingFinished(bool success);
    void savingProgressUpdate(int prog);
    void openVideoClicked();
    void saveDirClicked();
    void applyCoeffClicked();
    void removeCoeffClicked();
    void loadSettingsClicked();
    void addAreaClicked();
    void deleteAreaClicked();
    void saveSettingsClicked();
    void saveImgsClicked();
    void cancelSavingClicked();
    void playClicked();
    void stopClicked();
    void sliderMoved(int);

    void handleEditWidth(QString);
    void handleEditHeight(QString);
    void handleEditId(QString);

    void showPropertys(const QGraphicsRectItem&);
};

#endif