from camera import Camera
from mqtt_handler import MQTTHandler
from ImageParser import ImageParser
from enum import Enum
import json

class CameraModes(Enum):
    DISABLED = 0
    DOG_MODE = 1
    SURVEILLENCE = 2

class CameraHandler(MQTTHandler):
    def __init__(self, configFilePath, flip=False, fileType=".jpg", imageName="img_"):
        super().__init__(configFilePath);
        self.camera = Camera(flip, fileType, imageName);
        self.imageParser = ImageParser();
        self.mode = CameraModes.DISABLED.value

    def GetImage(self):
        frame = self.camera.GetFrame();
        img = self.imgParser.AddTimestamp(frame);
        img = self.imgParser.AddCPUTemp(img);
        return img;

    def GetOfflineImage(self):
        self.camera.GetOfflineFrame();

    def Enable(self):
        self.camera.Enable();

    def Disable(self):
        self.camera.Disable();

    def IsEnabled(self):
        return self.camera.IsEnabled();

    def StartMqtt(self):
        self.StartMQTT();

    def OnMessage(self, client, userdata, msg):
        print(f"Message received: {msg.payload.decode()} from topic: {msg.topic}")
        if msg.topic == self.config.GetSubscriptionTopics():
            self.mode = CameraModes(int(msg.payload.decode()));
            if self.mode == CameraModes.DISABLED:
                self.Disable()
            else:
                self.Enable()
            self.PublishCameraStatus()

    def OnConnect(self, client, userdata, flags, rc):
        if rc == 0:
            print("Connected to broker successfully!")
            # Subscribe to a topic
            client.subscribe(self.config.GetSubscriptionTopics())
            self.PublishCameraStatus();

        else:
            print(f"Failed to connect, return code {rc}")

    def PublishCameraStatus(self):
        topic = self.config.GetPublishTopic() + "status";
        message = {"cammera_connected": self.IsEnabled(), "mode": CameraModes(self.mode).value};
        jsonMessage = json.dumps(message);
        self.PublishMessage(topic, jsonMessage);
