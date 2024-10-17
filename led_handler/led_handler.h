#ifndef __LED_HANDLER_H__
#define __LED_HANDLER_H__

#include "mqtt_handler.h"
#include "config_handler.h"
#include "gpio.h"

typedef enum
{
    DISABLED,
    DOG_MODE,
    SURVEILLENCE
}SURVEILLENCE_MODES;

class LED_HANDLER : MQTT_HANDLER
{
    public:
        LED_HANDLER(const char* pinNumber);
        bool Initialize();
        void StartThread();
        void StopThread();
    private:
        CONFIG_HANDLER _ledConfig;
        GPIO _led;
        SURVEILLENCE_MODES _surveillenceMode = DOG_MODE;
        void _ledThread();
        bool _isRunning = false;

        void _MQTTThread() override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void connected(const std::string& cause) override;
        void connection_lost(const std::string& cause) override;
        void delivery_complete(mqtt::delivery_token_ptr token) override;
};

#endif //__LED_HANDLER_H__
