#include "socket_handler.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstring>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/writer.h"

SOCKET_HANDLER::SOCKET_HANDLER(const std::string filename) : _socketConfig(filename), _mqttHandler(filename)
{
}

SOCKET_HANDLER::~SOCKET_HANDLER()
{
    _mqttHandler.Stop();
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
    _serv_addr.sin_port = htons(_socketConfig.GetServerPort());

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, _socketConfig.GetServerAddress().c_str(), &_serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported\n";
        return false;
    }

    // Connect to the server
    if (connect(_sock, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0) {
        std::cerr << "Connection failed\n";
        return false;
    }

    std::cout << "Connection successful" << std::endl;

    _mqttHandler.Initialize();
    _mqttHandler.Start();

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
    rapidjson::Document document;

    while(_isRunning)
    {
        if(recv(_sock, _msg, sizeof(_msg) -1, 0) > 0)
        {
            std::cout << "Message from server: " << _msg << std::endl;
            if(document.Parse(_msg).HasParseError())
            {
                std::cerr << "Error: " << rapidjson::GetParseError_En(document.GetParseError())
                                       << " (" << document.GetErrorOffset()
                                       << ")" << std::endl;
            }
            else
            {
                rapidjson::Document mqttMsgDocument;
                mqttMsgDocument.SetObject();
                rapidjson::Document::AllocatorType& allocator = mqttMsgDocument.GetAllocator();
                if(document.HasMember("angle") && document["angle"].IsInt())
                {
                    std::cout << "/angle: " << document["angle"].GetInt() << std::endl;

                    uint8_t angleValue = document["angle"].GetInt();
                    mqttMsgDocument.AddMember("angle", angleValue, allocator);
                }

                if(document.HasMember("camera_mode") && document["camera_mode"].IsInt())
                {
                    std::cout << "camera_mode: " << document["camera_mode"].GetInt() << std::endl;

                    uint8_t camera_modeValue = document["camera_mode"].GetInt();
                    mqttMsgDocument.AddMember("camera_mode", camera_modeValue, allocator);
                }

                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                mqttMsgDocument.Accept(writer);

                _mqttHandler.PublishMessage(_socketConfig.GetPublishTopic(), buffer.GetString());
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cerr << "Socket thread stopped.. \n";
}

void SOCKET_HANDLER::_close()
{
    close(_sock);
}
