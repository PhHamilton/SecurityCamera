#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H
#include <string.h>
#include "mqtt_handler.h"
#include "config_handler.h"

typedef enum
{
    DISABLED,
    DOG_MODE,
    SURVEILLENCE
}SURVEILLENCE_MODES;

class CustomMQTTHandler : public MQTT_HANDLER
{
    public:
        CustomMQTTHandler(const std::string& configFilename) : MQTT_HANDLER(configFilename) {}
    protected:
    void _MQTTThread() override
    {
//        std::cerr << "Starting MQTT thread.." << std::endl;
        mqtt::const_message_ptr msg;
        _client->start_consuming();
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

    void connected(const std::string& cause) override
    {
        std::cout << "Camera handler connected to the MQTT-server" << std::endl;
    }

    void connection_lost(const std::string& cause) override
    {
        std::cout << "Camera handler lost connection to the MQTT-server" << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override
    {
        std::cout << "Message arrived:\n"
              << "Topic:" << msg->get_topic() << "\n"
              << "Payload:" << msg->to_string() << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override
    {

    }
    //std::cerr << "MQTT thread stopped.." << std::endl;
};

class CAMERA_HANDLER
{
    public:
        CAMERA_HANDLER(std::string outputFilepath);
        bool Initialize();
        void TakePicture();
    private:
        std::string _outputFilepath;
        int _cycle;

        SURVEILLENCE_MODES _surveillenceMode = DISABLED;
        CONFIG_HANDLER cameraConfig;
        CustomMQTTHandler mqttHandler;
};

#endif //CAMERA_HANDLER_H
