#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H
#include <string>
#include <vector>

class CONFIG_HANDLER
{
    public:
        CONFIG_HANDLER(const std::string filename);

        std::string GetClientID() {return _clientID;}
        std::string GetAddress() {return _address;}
        std::vector<std::string> GetSubscriptionTopics() {return _subscriptionTopics;}
        std::string GetPublishTopic() {return _publish_topic;}
        int GetQOS() {return _QOS;}
        int GetKeepAlive() {return _keepAlive;}
        std::string GetServerAddress() {return _serverAddress;}
        int GetServerPort() {return _serverPort;}
        int GetFramereate() {return _frameRate;}
        int GetImageCycleLimit() {return _imageCycleLimit;}
        bool GetVerticalFlip() {return _verticalFlip;}
        std::string GetOutputFilename() {return _outputFilename;};
   private:
        const std::string _filename;

        std::string _clientID;
        std::string _address;
        std::vector<std::string> _subscriptionTopics;
        std::string _publish_topic;
        int _QOS;
        int _keepAlive;

        std::string _serverAddress;
        int _serverPort;

        int _frameRate;
        int _imageCycleLimit;
        bool _verticalFlip;
        std::string _outputFilename;
};
#endif //CONFIG_HANDLER_H
