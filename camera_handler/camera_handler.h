#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H
#include <string.h>
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
};

#endif //CAMERA_HANDLER_H
