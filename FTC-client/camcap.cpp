#include "camcap.h"

CamCap::CamCap()
    : QQuickImageProvider(QQuickImageProvider::Image),
      mutex(PTHREAD_MUTEX_INITIALIZER), buff_mutex(PTHREAD_MUTEX_INITIALIZER)
{
    cap = cv::VideoCapture(0);
    if(!cap.isOpened()){ // check if we succeeded
        err(1, "Error opening default camera");
    }

    pthread_attr_t attr;
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    int ret = pthread_create(&thread_handle, &attr, CamCap::camStream_thread, this);

    if(ret != 0){
        err(1, "Couldn't create pthread on CamCap");
    }
}

CamCap::~CamCap()
{
    lock();
    pthread_cancel(thread_handle);
    lockBuff();
    m_imgBuffer.clear();
}

QImage CamCap::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

    qDebug() << "image requested";

    if(m_imgBuffer.isEmpty()){
        qDebug() << "Nothing returned";
        QImage im;
        im.fill(Qt::red);
        return im;
    }
    else{
        qDebug() << "Returned front of the queue";
        lockBuff();
        QImage im =  m_imgBuffer.takeFirst();
        unlockBuff();
        return im;
    }
}

void* CamCap::camStream_thread(void *arg)
{
    CamCap* self = static_cast<CamCap*>(arg);

    while(1){
        cv::Mat *frame = new cv::Mat;
        (self->cap) >> (*frame);
        cv::cvtColor(*frame, *frame, CV_BGR2RGB);

        const QImage image(frame->data, frame->cols, frame->rows, frame->step,
                           QImage::Format_RGB888, CamCap::matDeleter, frame);
        self->lockBuff();
        qDebug() << "Put frame to buffer";
        self->m_imgBuffer.push_back(image);
        self->unlockBuff();
        //        emit self->image_ready();
        usleep(100000);
    }

    return arg;
}

void CamCap::lock()
{
    pthread_mutex_lock(&mutex);
}

void CamCap::unlock()
{
    pthread_mutex_unlock(&mutex);
}

void CamCap::lockBuff()
{
    pthread_mutex_lock(&buff_mutex);
}

void CamCap::unlockBuff()
{
    pthread_mutex_unlock(&buff_mutex);
}
