#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <mqtt/client.h>
#include <mqtt/async_client.h>
#include "config_handler.h"
#include <string>

class mqtt_callback : public virtual mqtt::callback
{
    protected:
        void connected(const std::string& cause) override = 0;
        void connection_lost(const std::string& cause) override = 0;
        void message_arrived(mqtt::const_message_ptr msg) override = 0;
        void delivery_complete(mqtt::delivery_token_ptr token) override = 0;
};

class MQTT_HANDLER : protected mqtt_callback
{
    public:
        MQTT_HANDLER(const std::string filename);
        bool Initialize();
        bool Start();
        bool Stop();
        bool PublishMessage(std::string topic, std::string message);
        ~MQTT_HANDLER();
    protected:
        virtual void _MQTTThread() = 0;

        void connected(const std::string& cause) override
        {

        }
        void connection_lost(const std::string& cause) override
        {

        }

        void message_arrived(mqtt::const_message_ptr msg) override
        {
        }

        void delivery_complete(mqtt::delivery_token_ptr token) override
        {

        }

        bool _isRunning = false;
        mqtt::async_client* _client;

    private:
        CONFIG_HANDLER _mqttConfig;

        mqtt::connect_options _connOpts;

        std::string _clientID;
        std::string _serverAddress;
        std::string _publish_topic;

        int _QOS;
        int _keepAlive;

        std::vector<std::string> _subscriptionTopics;

};
#endif //MQTT_HANDLER_H
