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
        self.flipImage = None;
        self.fileType = None;
        self.imageName = None;
        self.resolution = None;
        self.imageWidth = None;
        self.imageHeight = None;
        self.frameRate = None;
        self.outputPath = None;

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

        self.clientID = self.GetConfigValue("MQTT", "client_id")
        self.address = self.GetConfigValue("MQTT", "address")
        self.port = self.GetConfigValue("MQTT", "port")
        self.subscriptionTopics = self.GetConfigValue("MQTT", "subscription_topics")
        self.publishTopic = self.GetConfigValue("MQTT", "publish_topic")
        self.QOS = self.GetConfigValue("MQTT", "QOS")
        self.keepAlive = self.GetConfigValue("MQTT", "keep_alive")

        self.flipImage = self.GetConfigValue("camera_parameters", "flip_image")
        self.fileType = self.GetConfigValue("camera_parameters", "file_type")
        self.imageName = self.GetConfigValue("camera_parameters", "image_name")
        self.width = self.GetConfigValue("camera_parameters", "width", "resolution")
        self.height = self.GetConfigValue("camera_parameters", "height", "resolution")
        self.frameRate = self.GetConfigValue("camera_parameters", "frame_rate")
        self.outputPath = self.GetConfigValue("camera_parameters", "output_path")
        self.nStoredImages = self.GetConfigValue("camera_parameters", "n_stored_images")


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

    def GetImageFlip(self):
        return self.flipImage;

    def GetFileType(self):
        return self.fileType;

    def GetImageName(self):
        return self.imageName;

    def GetResolution(self):
        return (self.width, self.height);

    def GetFrameRate(self):
        return self.frameRate;

    def GetOutputPath(self):
        return self.outputPath;

    def GetNStoredImages(self):
        return self.nStoredImages;

    def GetConfigValue(self, dictionary, key, subdict = None):
        if self.configFile is not None:
            configData = self.configFile.get(dictionary, {})
            if subdict is not None:
                configData = configData.get(subdict, {})
            value = configData.get(key);
            if value is None:
                print(f"Error: {key} is missing from the configuration file")
            else:
                print(f"{key}: {value} added!")
                return value
        else:
            print("Configuration data not loaded!");
            return None
