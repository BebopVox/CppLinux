#include <QCoreApplication> // delete if dont need Qt

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <iostream>

#include <breakermindsslserver.h>

using namespace std;

/*
void *worker_thread1(void *i)
{
    int j = 0;
    while(j < 25){
        // cout << "This is worker_thread() "  << i << "\n";
        printf("This is worker_thread #%ld loop: %ld \n", (long)i, (long)j);
        usleep((long)i*1000000);
        j++;
    }
    pthread_exit(NULL);
}
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // delete if dont need Qt

    BreakermindSslServer boom;
    boom.Start(3333,"/home/user/c++/qt/BreakermindServer/certificate.crt", "/home/user/c++/qt/BreakermindServer/private.key");

    /*
    pthread_t thread1;

    int i = 1, ret;

    while(i < 5){

        ret =  pthread_create(&thread1, NULL, &worker_thread1, (void *)i);
        if(ret != 0) {
                std::string s = to_string(i);
               cout << "Error: pthread_create() failed " <<  s << "\n ";
                exit(EXIT_FAILURE);
        }else{
            std::string s = to_string(i);
             cout << "In main: creating thread " << s << " \n";
        }
        i++;
    }
    */

    return a.exec(); // delete if dont need Qt
}

// Read more on:
// http://www.bogotobogo.com/cplusplus/multithreading_pthread.php
