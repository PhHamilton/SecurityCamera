#include "config_handler.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include <sstream>
#include <fstream>
#include <iostream>

CONFIG_HANDLER::CONFIG_HANDLER(const std::string filename)
{
    std::ifstream ifs(filename);

    if(!ifs.is_open())
    {
        std::cerr << "Could not open file" << filename << std::endl;
        return;
    }

    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document doc;

    doc.ParseStream(isw);

    if(doc.HasParseError())
    {
        std::cerr << "Error parsing JSON file." << std::endl;
        return;
    }

    if(doc.HasMember("MQTT") && doc["MQTT"].IsObject())
    {
        const rapidjson::Value& mqtt = doc["MQTT"];

        if(mqtt.HasMember("client_id") && mqtt["client_id"].IsString())
        {
            _clientID = mqtt["client_id"].GetString();
        }
        else
        {
            std::cerr << "\"client_id\" is missing or is not a string!" << std::endl;
        }

        if(mqtt.HasMember("address") && mqtt["address"].IsString())
        {
            _address = mqtt["address"].GetString();
        }
        else
        {
            std::cerr << "\"address\" is missing or is not a string!" << std::endl;
        }

        if(mqtt.HasMember("subscription_topics") && mqtt["subscription_topics"].IsArray())
        {
            const rapidjson::Value& values = mqtt["subscription_topics"];
            assert(values.IsArray());
            for(rapidjson::SizeType i = 0; i < values.Size(); i++)
                _subscriptionTopics.push_back(values[i].GetString());
        }
        else
        {
            std::cerr << "\"subscription_topics\" is missing or is not an array!" << std::endl;
        }


        if(mqtt.HasMember("publish_topic") && mqtt["publish_topic"].IsString())
        {
            _publish_topic = mqtt["publish_topic"].GetString();
        }
        else
        {
            std::cerr << "\"publish_topic\" is missing or is not a string!" << std::endl;
        }

        if(mqtt.HasMember("QOS") && mqtt["QOS"].IsInt())
        {
            _QOS = mqtt["QOS"].GetInt();
        }
        else
        {
            std::cerr << "\"QOS\" is missing or is not an int!" << std::endl;
        }

        if(mqtt.HasMember("keep_alive") && mqtt["keep_alive"].IsInt())
        {
            _keepAlive = mqtt["keep_alive"].GetInt();
        }
        else
        {
            std::cerr << "\"keep_alive\" is missing or is not an int!" << std::endl;
        }

    }
    if(doc.HasParseError())
    {
        std::cerr << "Error parsing JSON file." << std::endl;
        return;
    }

    if(doc.HasMember("socket") && doc["socket"].IsObject())
    {
        const rapidjson::Value& socket  = doc["socket"];

        if(socket.HasMember("server_address") && socket["server_address"].IsString())
        {
            _serverAddress = socket["server_address"].GetString();
        }
        else
        {
            std::cerr << "\"server_address\" is missing or is not a string!" << std::endl;
        }

        if(socket.HasMember("server_port") && socket["server_port"].IsInt())
        {
            _serverPort = socket["server_port"].GetInt();
        }
        else
        {
            std::cerr << "\"server_port\" is missing or is not an int!" << std::endl;
        }
    }
    if(doc.HasMember("camera_settings") && doc["camera_settings"].IsObject())
    {
        const rapidjson::Value& camera  = doc["camera_settings"];

        if(camera.HasMember("frame_rate") && camera["frame_rate"].IsInt())
        {
            _frameRate = camera["frame_rate"].GetInt();
        }
        else
        {
            std::cerr << "\"frame_rate\" is missing or is not an int!" << std::endl;
        }

        if(camera.HasMember("image_cycle_limit") && camera["image_cycle_limit"].IsInt())
        {
            _imageCycleLimit = camera["image_cycle_limit"].GetInt();
        }
        else
        {
            std::cerr << "\"image_cycle_limit\" is missing or is not an int!" << std::endl;
        }

        if(camera.HasMember("image_cycle_limit") && camera["image_cycle_limit"].IsInt())
        {
            _imageCycleLimit = camera["image_cycle_limit"].GetInt();
        }
        else
        {
            std::cerr << "\"image_cycle_limit\" is missing or is not an int!" << std::endl;
        }

        if(camera.HasMember("vertical_flip") && camera["vertical_flip"].IsBool())
        {
            _verticalFlip = camera["vertical_flip"].GetBool();
        }
        else
        {
            std::cerr << "\"image_cycle_limit\" is missing or is not an int!" << std::endl;
        }

        if(camera.HasMember("output_filename") && camera["output_filename"].IsString())
        {
            _outputFilename = camera["output_filename"].GetString();
        }
        else
        {
            std::cerr << "\"output_filename\" is missing or is not a string!" << std::endl;
        }
      }
}
