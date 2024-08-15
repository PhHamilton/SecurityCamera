#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <mqtt/client.h>
#include <mqtt/async_client.h>
#include "config_handler.h"
#include <string>

class mqtt_callback : public virtual mqtt::callback
{
    void connected(const std::string& cause) override
    {
        std::cout << "\nConnected: " << cause << std::endl;
    }

    void connection_lost(const std::string& cause) override
    {
        std::cout << "\nConnection lost: " << cause << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override
    {
        std::cout << "\nMessage arrived:\n"
                  << "Topic: " << msg->get_topic() << "\n"
                  << "Payload: " << msg->to_string() << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {
        std::cout << "\nDelivery complete for token: " << (token ? token->get_message_id() : -1) << std::endl;
    }
};

class MQTT_HANDLER
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
        bool _isRunning = false;
        mqtt::async_client* _client;

    private:
        CONFIG_HANDLER _mqttConfig;

        mqtt::connect_options _connOpts;
        mqtt_callback _callBack;

        std::string _clientID;
        std::string _serverAddress;
        std::string _publish_topic;

        int _QOS;
        int _keepAlive;

        std::vector<std::string> _subscriptionTopics;

};
#endif //MQTT_HANDLER_H
