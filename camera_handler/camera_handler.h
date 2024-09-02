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

class CAMERA_HANDLER : public MQTT_HANDLER
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
        void _MQTTThread() override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void connected(const std::string& cause) override;
        void connection_lost(const std::string& cause) override;
        void delivery_complete(mqtt::delivery_token_ptr token) override;
};

#endif //CAMERA_HANDLER_H
