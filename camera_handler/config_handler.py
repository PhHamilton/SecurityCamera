import json

class ConfigHandler(object):
    def __init__(self, filePath):
        self.filePath = filePath;
        self.configFile = None
        self.clientID = None;
        self.address = None;
        self.port = None;
        self.subscriptionTopics = None;
        self.publishTopic = None;
        self.QOS = None;
        self.keepAlive = None;

        self.ReadConfig()

    def ReadConfig(self):
        try:
            with open(self.filePath, "r") as config:
                self.configFile = json.load(config)

        except FileNotFoundError:
            print(f"Error: The file {self.filePath} was not found.")
            return None

        except json.JSONDecodeError:
            print(f"Error: The file {self.filePath} contains invalid JSON.")
            return None

        self.clientID = self.GetConfigValue("client_ID")
        self.address = self.GetConfigValue("address")
        self.port = self.GetConfigValue("port")
        self.subscriptionTopics = self.GetConfigValue("subscription_topics")
        self.publishTopic = self.GetConfigValue("publish_topic")
        self.QOS = self.GetConfigValue("QOS")
        self.keepAlive = self.GetConfigValue("keep_alive")

    def GetClientID(self):
        return self.clientID;

    def GetAddress(self):
        return self.address;

    def GetPort(self):
        return self.port;

    def GetSubscriptionTopics(self):
        return self.subscriptionTopics;

    def GetPublishTopic(self):
        return self.publishTopic;

    def GetQOS(self):
        return self.QOS;

    def GetKeepAlive(self):
        return self.keepAlive;

    def GetConfigValue(self, key):
        if self.configFile is not None:
            mqttConfig = self.configFile.get("MQTT", {})
            value = mqttConfig.get(key);
            if value is None:
                print(f"Error: {value} is missing from the configuration file")
            else:
                print(f"{key}: {value} added!")
                return value
        else:
            print("Configuration data not loaded!");
            return None
