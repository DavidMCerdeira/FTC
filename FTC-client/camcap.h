#ifndef CAMCAP_H
#define CAMCAP_H

#include <QQuickImageProvider>
#include <QImage>
#include <QQueue>
#include <pthread.h>
#include <err.h>
#include <controller.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <unistd.h> //usleep

class CamCap: public QQuickImageProvider
{
    pthread_t thread_handle;
    pthread_mutex_t mutex;
    cv::VideoCapture cap;
    QQueue<QImage> m_imgBuffer;
    pthread_mutex_t buff_mutex;

public:
    CamCap();
    ~CamCap();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

    void lock();
    void unlock();

private:
    static void *camStream_thread(void *arg);
    static void matDeleter(void* mat) { delete static_cast<cv::Mat*>(mat); }

    void lockBuff();
    void unlockBuff();
};

#endif // CAMCAP_H
