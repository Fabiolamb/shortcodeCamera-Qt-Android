#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QMediaDevices>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void captureImage();
    void updateExposure(int value);
    void updateFocus(int value);

private:
    void initPermissions();
    void init();

    QCamera *camera;
    QImageCapture *imageCapture;
    QMediaCaptureSession captureSession;
    QVideoWidget *viewfinder;
    QPushButton *captureButton;
    QSlider *exposureSlider;
    QSlider *focusSlider;
    QWidget *centralWidget;
    QVBoxLayout *layout;
};

#endif // MAINWINDOW_H
