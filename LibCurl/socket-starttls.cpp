// Add after accept client connections and fork() or in thread loop:
// int client = accept(sock, (struct sockaddr*)&addr, &len);
// pid = fork();
// waitForStarttls(1,client);

void BreakermindSslServer::waitForStarttls(int requiretls, int client){
    try{
        char *welcome = (char *)"220 Hello ESMTP STARTTLS \r\n";
        char *ehlo = (char *)"250-qflash.pl at your service\r\n250-SIZE 157286400\r\n250 STARTTLS\r\n";
        char *ok = (char *)"250 Ok\r\n";
        char *data = (char *)"354 send data\r\n";
        char *end = (char *)"250 email was send\r\n";
        char *bye = (char *)"221 Bye...\r\n";
        char *err = (char *)"500 Erro command not allowed\r\n";
        char *tls = (char *)"220 Ready to start TLS\r\n";
        char *require = (char *)"530 STARTTLS command first\r\n";

        char buffer[1024] = {0};
        int server_fd, new_socket, valread;

        // Clear buffer
        buffer[0] = '\0';
        memset(buffer,0,sizeof(buffer));

        // welcome message
        send(client , welcome , strlen(welcome) , 0 );

        while(1){
            // ehlo
            memset(buffer,0,sizeof(buffer));
            valread = read(client, buffer, 1024);
            printf("Client send %s\n",buffer );

            if(Contain(std::string(buffer),"STARTTLS") || Contain(std::string(buffer),"starttls")){
                char *tls1 = (char *)"220 Ready to start TLS\r\n";
                send(client, tls1, strlen(tls1), 0);
                // end while loop and start tls connection
                break;
            }else if(Contain(std::string(buffer),"ehlo") || Contain(std::string(buffer),"helo") || Contain(std::string(buffer),"EHLO") || Contain(std::string(buffer),"HELO")){
                send(client, ehlo, strlen(ehlo), 0);
            }else{
                send(client, require, strlen(require), 0);
            }
            /*
            if(Contain(std::string(buffer),"STARTTLS") || Contain(std::string(buffer),"starttls")){
                memset(buffer,0,sizeof(buffer));
                send(new_socket, tls, strlen(tls), 0);
                break; // end while loop
            }else if(Contain(std::string(buffer),"ehlo") || Contain(std::string(buffer),"helo") || Contain(std::string(buffer),"EHLO") || Contain(std::string(buffer),"HELO")){
                memset(buffer,0,sizeof(buffer));
                send(new_socket, ehlo, strlen(ehlo), 0);
            }else if(Contain(std::string(buffer),"mail from:") || Contain(std::string(buffer),"MAIL FROM:")){
                memset(buffer,0,sizeof(buffer));
                send(new_socket, ok, strlen(ok), 0);
            }else if(Contain(std::string(buffer),"rcpt to:") || Contain(std::string(buffer),"RCPT TO:")){
                memset(buffer,0,sizeof(buffer));
                send(new_socket, ok, strlen(ok), 0);
            }else if(Contain(std::string(buffer),"DATA")){
                memset(buffer,0,sizeof(buffer));
                send(new_socket, data, strlen(data), 0);
            }else if(Contain(std::string(buffer),"quit") || Contain(std::string(buffer),"QUIT")){
                memset(buffer,0,sizeof(buffer));
                send(new_socket, bye, strlen(bye), 0);
                close(client);
                kill(pid,SIGTERM);
            }else if(Contain(std::string(buffer),".\r\n")){
                memset(buffer,0,sizeof(buffer));
                send(new_socket, end, strlen(end), 0);
            }else if(1){
                memset(buffer,0,sizeof(buffer));
                send(new_socket, err, strlen(err), 0);
            }
            */
        }
    }catch(std::exception &ee){
        // ee.wath();
        send(client, require, strlen(require), 0);
    }
}
