#include "mqtt_handler.h"

MQTT_HANDLER::MQTT_HANDLER(const std::string filename):
    _client(nullptr),
    _mqttConfig(filename)
{
}

MQTT_HANDLER::~MQTT_HANDLER()
{
    Stop();
    if(_client)
    {
        delete _client;
    }
}

bool MQTT_HANDLER::Initialize()
{
    try
    {
        _client = new mqtt::async_client(
                                          _mqttConfig.GetAddress(),
                                          _mqttConfig.GetClientID()
                                         );
        _client->set_callback(*this);
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        return false;
    }

    return true;
}

bool MQTT_HANDLER::Start()
{
    try
    {
        _connOpts.set_clean_session(true);
        std::cout << "Connecting to the MQTT server...\n";
        _client->connect(_connOpts)->wait();
        std::cout << "Connected!" << std::endl;

        std::vector<std::string> topics = _mqttConfig.GetSubscriptionTopics();
        for(const auto& topic : topics)
        {
            _client->subscribe(topic, 1);
        }

        _isRunning = true;

        std::thread(&MQTT_HANDLER::_MQTTThread, this).detach();
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        return false;
    }

    return true;
}

bool MQTT_HANDLER::PublishMessage(std::string topic, std::string message)
{
    try
    {
        auto msg = mqtt::make_message(
                                         topic,
                                         message
                                     );
        msg->set_qos(_mqttConfig.GetQOS());

        _client->publish(msg)->wait_for(std::chrono::seconds(10));
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Wait to receive messages
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        return false;
    }
    return true;
}

bool MQTT_HANDLER::Stop()
{
    if(!_isRunning) return false;

    if(!_client || !_client->is_connected())
    {
        std::cerr << "Client is not connected or not initialized. \n";
        return false;
    }
    try
    {
        std::cout << "Disconnecting from the MQTT server...\n";
        _client->disconnect()->wait();
        std::cout << "Disconnected!" << std::endl;
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        return false;
    }

    _isRunning = false;
    return true;
}

