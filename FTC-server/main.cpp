#include <iostream>
#include <pthread.h>
#include "server.h"
#include <signal.h>
#include <syslog.h>

using namespace std;

Server *FTCserver;

void closingAct(int sig, siginfo_t *si, void *ucontext)
{
    delete FTCserver;
    exit(0);
}

int main()
{
    struct sigaction sigTerm_act;
    sigset_t ftc_sig_set;

    /* unblocking terminate signal */
    sigfillset(&ftc_sig_set);
    sigdelset(&ftc_sig_set, SIGTERM);
    pthread_sigmask(SIG_BLOCK ,&ftc_sig_set, NULL);

    sigTerm_act.sa_sigaction = closingAct;
    sigTerm_act.sa_flags = SA_SIGINFO;

    if(sigaction(SIGTERM, &sigTerm_act, NULL) == -1)
        syslog(LOG_ERR, "FTC_Main: Sigaction error");

    FTCserver = new Server();

    pthread_exit(NULL);
}
