from camera import Camera
from mqtt_handler import MQTTHandler
from ImageParser import ImageParser
from enum import Enum
import json
import threading

class CameraModes(Enum):
    DISABLED = 0
    DOG_MODE = 1
    SURVEILLENCE = 2

class CameraHandler(MQTTHandler):
    def __init__(self, configFilePath, flip=False, fileType=".jpg", imageName="img_"):
        super().__init__(configFilePath)
        self.camera = Camera(flip, fileType, imageName)
        self.imageParser = ImageParser()
        self.mode = CameraModes.DISABLED.value
        self.camera_lock = threading.Lock()  # Thread lock to prevent race conditions

    def GetImage(self):
        with self.camera_lock:
            frame = self.camera.GetFrame()
            img = self.imageParser.AddTimestamp(frame)
            img = self.imageParser.AddCPUTemp(img)
            return img

    def GetOfflineImage(self):
        with self.camera_lock:
            return self.camera.GetOfflineFrame()

    def Enable(self):
        with self.camera_lock:
            self.camera.Enable()

    def Disable(self):
        with self.camera_lock:
            self.camera.Disable()

    def IsEnabled(self):
        return self.camera.IsEnabled()

    def StartMqtt(self):
        self.StartMQTT()

    def OnMessage(self, client, userdata, msg):
        print(f"Message received: {msg.payload.decode()} from topic: {msg.topic}")
        if msg.topic == self.config.GetSubscriptionTopics():
            self.mode = CameraModes(int(msg.payload.decode()))
            if self.mode == CameraModes.DISABLED:
                self.Disable()
            else:
                self.Enable()
            self.PublishCameraStatus()

    def OnConnect(self, client, userdata, flags, rc):
        if rc == 0:
            print("Connected to broker successfully!")
            client.subscribe(self.config.GetSubscriptionTopics())
            self.PublishCameraStatus()
        else:
            print(f"Failed to connect, return code {rc}")

    def PublishCameraStatus(self):
        topic = self.config.GetPublishTopic() + "status"
        message = {"camera_connected": self.IsEnabled(), "mode": CameraModes(self.mode).value}
        jsonMessage = json.dumps(message)
        self.PublishMessage(topic, jsonMessage)
