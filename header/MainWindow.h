#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#define UNUSED(x) (void)(x)

//Forward declarations 
namespace Ui {
    class MainWindow;
}
class LiveCaptureWidget;
class VideoWidget;
class ImageScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ImageScene& getImageScene();
    QSize getImageViewSize();
public slots:
    void setImage(QImage);
    
private slots:
    void onRadioButtonClicked();

private:
    Ui::MainWindow *m_ui;
    LiveCaptureWidget *m_liveCaptureWidget = nullptr;
    VideoWidget *m_videoWidget = nullptr;
    ImageScene* m_imageView;

    void resizeEvent(QResizeEvent* event);
    void deleteWidget();
};

#endif // MAINWINDOW_H