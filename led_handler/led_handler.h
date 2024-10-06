#ifndef __LED_HANDLER_H__
#define __LED_HANDLER_H__

#include "mqtt_handler.h"
#include "config_handler.h"
#include "gpio.h"

class LED_HANDLER : MQTT_HANDLER
{
    public:
        LED_HANDLER(const char* pinNumber);
        bool Initialize();
    private:
        CONFIG_HANDLER _ledConfig;
        GPIO _led;

        void _MQTTThread() override;
        void message_arrived(mqtt::const_message_ptr msg) override;
        void connected(const std::string& cause) override;
        void connection_lost(const std::string& cause) override;
        void delivery_complete(mqtt::delivery_token_ptr token) override;
};

#endif //__LED_HANDLER_H__
