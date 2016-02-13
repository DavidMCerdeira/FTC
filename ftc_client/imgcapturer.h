#ifndef IMGCAPTURER_H
#define IMGCAPTURER_H

#include <pthread.h>

class ImgCapturer
{
public:
    ImgCapturer();

    int captureStableFace();
    void stopCapture();

private:
    void *captureStableFace_thread(void *arg);
};

#endif // IMGCAPTURER_H
