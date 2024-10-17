#include "led_handler.h"
#include <thread>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/writer.h"

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

void LED_HANDLER::StartThread()
{
    _isRunning = true;
    std::thread(&LED_HANDLER::_ledThread, this).detach();
}

void LED_HANDLER::_ledThread()
{
    while(_isRunning)
    {
        switch(_surveillenceMode)
        {
            case DISABLED:
            {
                if(strcmp(_led.Get(), "0") == 0)
                {
                    continue;
                }
                else
                {
                    _led.TurnOff();
                }
            }
            break;
            case DOG_MODE:
            {
                _led.Toggle();
            }
            break;
            case SURVEILLENCE:
            {
                _led.TurnOn();
            }
            break;
            default:
            {

            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void LED_HANDLER::StopThread()
{
    _isRunning = false;
}

void LED_HANDLER::_MQTTThread()
{

}
void LED_HANDLER::message_arrived(mqtt::const_message_ptr msg)
{
    std::cout << "Handling message for topic: " << msg->get_topic() << " with payload: " << msg->to_string() << std::endl;
    _surveillenceMode = (SURVEILLENCE_MODES) (msg->to_string()[0] - 0x30);
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

