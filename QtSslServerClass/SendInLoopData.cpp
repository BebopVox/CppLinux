        // Send attachment data
        SSL_write(ssl, reply_html, strlen(reply_html));        
        std::string html = "";
        if (received > 0)
        {
            html += std::string(buffer);
            TotalReceived += received;
            while(1){
                received = SSL_read (ssl, buffer, readSize);
                html += buffer;
                TotalReceived += received;
                // printf("PID %i Buffsize - %i - %.*s \n", getpid(), received, received, buffer);
                cout << "MAIL FROM <<< " << std::string(buffer) << endl;
                string xx ="";
                string en = "[end]";
                xx = std::string(buffer);
                // if(x.find(std::string("[end]")) != std::string::npos){
                if(strstr(xx.c_str(),en.c_str())){
                    cout << "SHOW HTML " << html;
                    // Clear buffer
                    memset(buffer, 0, sizeof buffer);
                    break;
                }
                // check ssl error and destroy connection
                sslError(ssl, received);
            }
        }
