#include <QCoreApplication> // delete if dont need Qt

// http://www.bogotobogo.com/cplusplus/multithreading_pthread.php

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <iostream>

using namespace std;

void *worker_thread(void *i)
{
    while(1){
        cout << "This is worker_thread() "  << i << "\n";
        printf("This is worker_thread #%ld \n", (long)i);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // delete if dont need Qt

    pthread_t thread1;

    int i = 1, ret;

    while(i < 5){

        ret =  pthread_create(&thread1, NULL, &worker_thread, (void *)i);
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

    return a.exec(); // delete if dont need Qt
}

