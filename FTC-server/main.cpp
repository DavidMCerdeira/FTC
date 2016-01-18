#include <iostream>
#include <pthread.h>
#include "server.h"

using namespace std;

int main()
{
    Server myServer(2);
    pthread_exit(0);
}
