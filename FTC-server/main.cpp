#include <iostream>
#include <pthread.h>
#include "server.h"
#include <signal.h>

using namespace std;

int main()
{
    Server *myServer;
    sigset_t ftc_sig_set;

    sigfillset(&ftc_sig_set);
    pthread_sigmask(SIG_BLOCK ,&ftc_sig_set, NULL);

    myServer = new Server();

    pthread_exit(NULL);
}
