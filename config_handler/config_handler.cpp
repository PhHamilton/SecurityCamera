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
}
