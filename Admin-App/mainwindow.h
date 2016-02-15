#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <qmediarecorder.h>
#include <qcameraviewfinder.h>
#include "register.h"
#include "searchemployee.h"
#include "sendmessage.h"
#include "terminalflow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Register regist;
    SearchEmployee search;
    SendMessage sendMsg;
    TerminalFlow flow;
    QCamera *camera;
    QCameraImageCapture *imageCapture;
    bool isTakingPhoto;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void setCamera(QCameraInfo cameraInfo);

private slots:
    void slot_tabChanged(int idx);

    /* regist tab--> */
    void regist_name();
    void regist_contact();
    void regist_email();
    //void regist_photo();
    void regist_commit();
    /* camera--> */
    void camera_select();
    void camera_readyForCapture(bool ready);
    void camera_captureImage(int requestId, QImage img);
    void camera_takePicture();
    /* <--camera */
    /* <--regist tab */

    /* search tab--> */
    void search_name();
    void search_commit();
    /* <--search tab */

    /* send message tab--> */
    void sendMsg_commit();
    /* <--send message tab */

    void quit();
};

#endif // MAINWINDOW_H
