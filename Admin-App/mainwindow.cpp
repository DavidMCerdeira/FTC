#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), isTakingPhoto(false)
{
    QString name, password;
    LoginDialog *login = new LoginDialog(&name, &password);
    connect(login, SIGNAL(rejected()), this, SLOT(quit()));
    login->exec();

    qDebug() << name << password;
    /* validate */

    QStringList departments;
    QStringList jobs;
    QStringList permissions;

    departments.push_back("Lol1");
    departments.push_back("Lol2");
    departments.push_back("Lol3");

    jobs.push_back("top1");
    jobs.push_back("top2");
    jobs.push_back("top3");

    permissions.push_back("No Priviledge");
    permissions.push_back("Priviledged");
    permissions.push_back("Admin");

    ui->setupUi(this);
    connect(ui->tabs, SIGNAL(currentChanged(int)), this, SLOT(slot_tabChanged(int)));

    /* regist tab--> */
    camera = new QCamera;
    imageCapture = new QCameraImageCapture(0);

    ui->regist_cameraPushButton->setEnabled(false);
    connect(ui->regist_addUserPushButton, SIGNAL(pressed()), this, SLOT(regist_commit()));
    connect(ui->regist_cameraPushButton, SIGNAL(pressed()), this, SLOT(camera_takePicture()));
    ui->regist_departmentsComboBox->insertItems(0, departments);
    ui->regist_jobComboBox->insertItems(0, jobs);
    ui->regist_permissionComboBox->insertItems(0, permissions);

    /* camera--> */
    setCamera(QCameraInfo::defaultCamera());
    //    foreach (const QCameraInfo &cameraInfo, QCameraInfo::availableCameras()) {
    //        ui->regist_cameraComboBox->insertItem(ui->regist_cameraComboBox->count(), cameraInfo.description(), QVariant::fromValue(cameraInfo));
    //    }
    /* <--camera */
    /* <--regist tab */

    /* search tab--> */
    connect(ui->search_searchPushButton, SIGNAL(pressed()), this, SLOT(search_commit()));
    ui->search_departmentsComboBox->insertItems(0, departments);
    ui->search_jobsComboBox->insertItems(0, jobs);
    ui->search_permissionsComboBox->insertItems(0, permissions);
    /* <--search tab */

    /* send message tab--> */
    connect(ui->msgs_sendPushButton, SIGNAL(pressed()), this, SLOT(sendMsg_commit()));
    /* <--send message tab */

    /* flow tab--> */
    connect(ui->flow_autoUpdateCheckBox, SIGNAL(clicked(bool)), &flow, SLOT(setAutoUpdate(bool)));
    connect(ui->flow_reloadPushButton, SIGNAL(pressed()), &flow, SLOT(checkForData()));
    ui->flow_autoUpdateCheckBox->setChecked(true);
    flow.setTable(ui->flow_tableWidget);
    flow.setAutoUpdate(true);
    /* <--flow tab*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCamera(QCameraInfo cameraInfo)
{
    delete imageCapture;
    delete camera;

    camera = new QCamera(cameraInfo);

    imageCapture = new QCameraImageCapture(camera);

    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(camera_captureImage(int,QImage)));
    connect(imageCapture, SIGNAL(readyForCaptureChanged(bool)), this, SLOT(camera_readyForCapture(bool)));
    connect(imageCapture, SIGNAL(error(int,QCameraImageCapture::Error,QString)), this,
            SLOT(displayCaptureError(int,QCameraImageCapture::Error,QString)));

    //    connect(ui->regist_cameraPushButton, SIGNAL(pressed()), , SLOT());

    camera->setViewfinder(ui->cameraOutput);
    camera->start();
}

void MainWindow::slot_tabChanged(int idx)
{
    switch(idx){
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        qDebug() << "Literally wtf!?!?";
        break;
    }
}

void MainWindow::regist_name()
{
    regist.setName(ui->regist_nameLineEdit->text());
}

void MainWindow::regist_contact()
{
    regist.setContactNumber(ui->regist_contactLineEdit->text());
}

void MainWindow::regist_email()
{
    regist.setEmail(ui->regist_emailLineEdit->text());
}

void MainWindow::regist_commit()
{
    regist.setName(ui->regist_nameLineEdit->text());
    regist.setContactNumber(ui->regist_contactLineEdit->text());
    regist.setEmail(ui->regist_emailLineEdit->text());
    regist.setDepartIdx(ui->regist_departmentsComboBox->currentIndex());
    regist.setJobsIdx(ui->regist_jobComboBox->currentIndex());
    regist.setPermissionsIdx(ui->regist_permissionComboBox->currentIndex());
    regist.setBirth(ui->regist_birthDateEdit->date());
    regist.commitUser();
}

void MainWindow::camera_select()
{
    //    setCamera(static_cast<QCameraInfo>(ui->regist_cameraComboBox->currentData(ui->regist_cameraComboBox->currentIndex())));
    setCamera(QCameraInfo::defaultCamera());
}

void MainWindow::camera_readyForCapture(bool ready)
{
    ui->regist_cameraPushButton->setEnabled(ready);
}

void MainWindow::camera_captureImage(int requestId, QImage img)
{
    Q_UNUSED(requestId);

    regist.addFace(img);

    isTakingPhoto = false;
}

void MainWindow::camera_takePicture()
{
    if(!isTakingPhoto){
        isTakingPhoto = true;
        imageCapture->capture();
    }
}

void MainWindow::search_name()
{
    search.setName(ui->search_idLineEdit->text());
}

void MainWindow::search_commit()
{
    search.setName(ui->search_idLineEdit->text());
    search.setDepartIdx(ui->search_departmentsComboBox->currentIndex());
    search.setJobsIdx(ui->search_jobsComboBox->currentIndex());
    search.setPermissions(ui->search_permissionsComboBox->currentIndex());
    search.commit();
}

void MainWindow::sendMsg_commit()
{
    sendMsg.setId(ui->msgs_idLineEdit->text());
    sendMsg.setBroadcast((ui->msgs_broadCastCheckBox->checkState() == Qt::Unchecked) ? false : true);
    sendMsg.setMsg(ui->msgs_messageTextEdit->toPlainText());
    sendMsg.commit();
}

void MainWindow::quit()
{
    exit(0);
}

