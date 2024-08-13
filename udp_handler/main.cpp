#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <cstring>

#define PORT 8080
#include "socket_handler.h"

#include "../mqtt_handler/mqtt_handler.h"
#include "../config_handler/config_handler.h"
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
                    std::cerr << "Lost connection to the MQTT server. Reconnecting...\n";
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

int main(int argc, char* argv[])
{
    SOCKET_HANDLER socketHandler("config/config.json");
    socketHandler.Initialize();
    socketHandler.Connect();
    socketHandler.SendData("test message");

    while(1);

    CustomMQTTHandler mqttHandler("config/config.json");
    mqttHandler.Initialize();
    mqttHandler.Start();
    mqttHandler.PublishMessage("Testmeddelande");
    mqttHandler.Stop();

    return 0;
}
