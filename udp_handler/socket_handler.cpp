#include "socket_handler.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstring>

SOCKET_HANDLER::SOCKET_HANDLER(const std::string filename) : _socketConfig(filename)
{
}

SOCKET_HANDLER::~SOCKET_HANDLER()
{
    _close();
}
bool SOCKET_HANDLER::Initialize()
{
    if((_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error\n";
        return false;
    }

    std::cout << "Socket created" << std::endl;

    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.1.209", &_serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported\n";
        return false;
    }

    // Connect to the server
    if (connect(_sock, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return false;
    }

    std::cout << "Connection successful" << std::endl;

    return true;
}

void SOCKET_HANDLER::Connect()
{
    _isRunning = true;
    std::thread(&SOCKET_HANDLER::_socketThread, this).detach();
}

void SOCKET_HANDLER::Disconnect()
{
    _isRunning = false;
    _close();
}

void SOCKET_HANDLER::SendData(const char* message)
{
    send(_sock, message, strlen(message), 0);
}

void SOCKET_HANDLER::_socketThread()
{
    std::cerr << "Socket MQTT thread.. \n";

    while(_isRunning)
    {
        if(read(_sock, _msg, BUFFER_SIZE) > 0)
        {
            std::cerr << "Message from server: " << _msg << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cerr << "Socket thread stopped.. \n";
}

void SOCKET_HANDLER::_close()
{
    close(_sock);
}
