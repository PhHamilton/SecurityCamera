#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

#include "config_handler.h"
#include "mqtt_handler.h"
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

class CustomMQTTHandler : public MQTT_HANDLER
{
    public:
        CustomMQTTHandler(const std::string& configFilename) : MQTT_HANDLER(configFilename) {}
    protected:
    void _MQTTThread() override
    {
//        std::cerr << "Starting MQTT thread.." << std::endl;
        while (_isRunning)
        {
            try
            {
                if (!_client->is_connected())
                {
                    std::cerr << "Lost connection to the MQTT server. Reconnecting..." << std::endl;
                    _client->reconnect()->wait();
                    std::cerr << "Reconnected!" << std::endl;
                }

                // Decompose Message!
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            catch (const mqtt::exception& exc)
            {
                std::cerr << "Error: " << exc.what() << std::endl;
            }
        }
    }
    //std::cerr << "MQTT thread stopped.." << std::endl;
};

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
        CustomMQTTHandler _mqttHandler;
        int _sock;
        char _msg[BUFFER_SIZE] = {0};
        struct sockaddr_in _serv_addr;
        bool _isRunning = false;

        void _close();
        void _socketThread();
};
#endif //SOCKET_HANDLER_H
