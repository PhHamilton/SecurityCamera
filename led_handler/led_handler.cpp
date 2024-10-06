#include "led_handler.h"

LED_HANDLER::LED_HANDLER(const char* pinNumber)
    : _led(pinNumber), _ledConfig("config/config.json"),
      MQTT_HANDLER("config/config.json")
{
}

bool LED_HANDLER::Initialize()
{
    MQTT_HANDLER::Initialize();
    MQTT_HANDLER::Start();
    _led.Set(GPIO_MODE::OUTPUT);
}
void LED_HANDLER::_MQTTThread()
{

}
void LED_HANDLER::message_arrived(mqtt::const_message_ptr msg)
{
    std::cout << "Handling message for topic: " << msg->get_topic() << " with payload: " << msg->to_string() << std::endl;
}
void LED_HANDLER::connected(const std::string& cause)
{
    std::cout << "Connected: " << cause << std::endl;
}
void LED_HANDLER::connection_lost(const std::string& cause)
{
    std::cout << "Connection lost: " << cause << std::endl;
}
void LED_HANDLER::delivery_complete(mqtt::delivery_token_ptr token)
{

    std::cout << "Delivery complete for token: " << (token ? token->get_message_id() : -1) << std::endl;
}

