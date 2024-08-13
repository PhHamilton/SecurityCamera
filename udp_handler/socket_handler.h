#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

#include "config_handler.h"
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

class SOCKET_HANDLER
{
    public:
        SOCKET_HANDLER(const std::string filename);
        bool Initialize();
        void Connect();
        void Disconnect();
        void SendData(const char* message);
        ~SOCKET_HANDLER();
    private:
        CONFIG_HANDLER _socketConfig;
        int _sock;
        char* _msg[BUFFER_SIZE] = {0};
        struct sockaddr_in _serv_addr;
        bool _isRunning = false;

        void _close();
        void _socketThread();
};
#endif //SOCKET_HANDLER_H
