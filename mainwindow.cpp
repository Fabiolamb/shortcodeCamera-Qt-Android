#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCamera>
#include <QMediaDevices>
#include <QImageCapture>
#include <QApplication>

#if QT_CONFIG(permissions)
#include <QPermission>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    camera(new QCamera(QMediaDevices::defaultVideoInput())),
    imageCapture(new QImageCapture),
    viewfinder(new QVideoWidget),
    captureButton(new QPushButton("Capture")),
    exposureSlider(new QSlider(Qt::Horizontal)),
    focusSlider(new QSlider(Qt::Horizontal)),
    centralWidget(new QWidget(this)),
    layout(new QVBoxLayout(centralWidget))
{
    setCentralWidget(centralWidget);

    layout->addWidget(viewfinder);
    layout->addWidget(captureButton);

#if QT_CONFIG(permissions)
    // Camera permission
    QCameraPermission cameraPermission;
    switch (qApp->checkPermission(cameraPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cameraPermission, this, &MainWindow::initPermissions);
        return;
    case Qt::PermissionStatus::Denied:
        qWarning("Camera permission is not granted!");
        return;
    case Qt::PermissionStatus::Granted:
        break;
    }
#endif

    init();
}

void MainWindow::initPermissions()
{
#if QT_CONFIG(permissions)
    // Camera permission
    QCameraPermission cameraPermission;
    if (qApp->checkPermission(cameraPermission) != Qt::PermissionStatus::Granted) {
        qWarning("Camera permission is not granted!");
        return;
    }
#endif

    init();
}

void MainWindow::init()
{
    captureSession.setCamera(camera);
    captureSession.setVideoOutput(viewfinder);
    captureSession.setImageCapture(imageCapture);

    connect(captureButton, &QPushButton::clicked, this, &MainWindow::captureImage);
    connect(exposureSlider, &QSlider::valueChanged, this, &MainWindow::updateExposure);
    connect(focusSlider, &QSlider::valueChanged, this, &MainWindow::updateFocus);

    camera->start();
}


MainWindow::~MainWindow()
{
    delete camera;
    delete imageCapture;
    delete viewfinder;
    delete captureButton;
    delete exposureSlider;
    delete focusSlider;
    delete layout;
    delete centralWidget;
}

void MainWindow::captureImage()
{
    imageCapture->captureToFile();
}

void MainWindow::updateExposure(int value)
{
    camera->setExposureCompensation(value / 10.0);
}

void MainWindow::updateFocus(int value)
{
    // 使用自定义的焦距更新逻辑
    // camera->focus()->setFocusPointMode(QCameraFocus::CustomFocusPoint);
    // camera->focus()->zoomTo(value / 100.0, 1.0);
}
