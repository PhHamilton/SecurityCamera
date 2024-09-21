#include "camera_handler.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <signal.h>
#include <unistd.h>

CAMERA_HANDLER::CAMERA_HANDLER(std::string outputFilepath)
    : _outputFilepath(outputFilepath), _cycle(0), _surveillenceMode(DISABLED),
      cameraConfig("config/config.json"), MQTT_HANDLER("config/config.json")

{
}

bool CAMERA_HANDLER::Initialize()
{
    MQTT_HANDLER::Initialize();
    MQTT_HANDLER::Start();
}

void CAMERA_HANDLER::_MQTTThread()
{

}

void CAMERA_HANDLER::message_arrived(mqtt::const_message_ptr msg)
{
    std::cout << "Handling message for topic: " << msg->get_topic() << " with payload: " << msg->to_string() << std::endl;
}

void CAMERA_HANDLER::connected(const std::string& cause)
{
    std::cout << "Connected: " << cause << std::endl;
}

void CAMERA_HANDLER::connection_lost(const std::string& cause)
{
    std::cout << "Connection lost: " << cause << std::endl;
}

void CAMERA_HANDLER::delivery_complete(mqtt::delivery_token_ptr token)
{
    std::cout << "Delivery complete for token: " << (token ? token->get_message_id() : -1) << std::endl;
}

void CAMERA_HANDLER::TakePicture()
{
    if((fork()) != 0)
        std::cerr << "Failed to duplicate process.." << std::endl;

    std::ostringstream ss;
    int width = std::to_string(cameraConfig.GetImageCycleLimit() - 1).length();
    ss << cameraConfig.GetOutputFilename() << std::setw(width) << std::setfill('0') << _cycle;

    if(cameraConfig.GetVerticalFlip() == true)
    {
        execl("/user/bin/raspistill",
              "/user/bin/raspistill",
              "-n",
              "-vf",
              "-o",
              ss.str(),
              NULL
             );
    }
    else
    {
        execl("/user/bin/raspistill",
          "/user/bin/raspistill",
          "-n",
          "-o",
          ss.str(),
          NULL
         );

    }
}
