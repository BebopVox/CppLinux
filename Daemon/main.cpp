#include "demonize.cpp"

int main()
{
    //Start daemon first
    skeleton_daemon();

    while (1)
    {        
        // Do jobs in loop
        syslog (LOG_NOTICE, "First daemon started...");
        // Wait 5 second
        sleep (5);      
        // usleep(5000000);
    }

    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}
