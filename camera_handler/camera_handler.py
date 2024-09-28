from camera import Camera
from mqtt_handler import MQTTHandler
from image_parser import ImageParser
from config_handler import ConfigHandler
from enum import Enum
import json
import threading

class CameraModes(Enum):
    DISABLED = 0
    DOG_MODE = 1
    SURVEILLENCE = 2

class CameraHandler(MQTTHandler):
    def __init__(self, configFilePath):
        super().__init__(configFilePath)
        self.cameraConfig = ConfigHandler(configFilePath)
        self.camera = Camera(self.cameraConfig)
        self.imageParser = ImageParser()
        self.mode = CameraModes.DISABLED.value
        self.camera_lock = threading.Lock()  # Thread lock to prevent race conditions
        self.imageCounter = 1;

    def GetImage(self):
        with self.camera_lock:
            frame = self.camera.GetFrame()
            img = self.imageParser.AddTimestamp(frame)
            img = self.imageParser.AddCPUTemp(img)
            if self.mode == CameraModes.DOG_MODE and self.imageCounter <= self.cameraConfig.GetNStoredImages():
                paddingLength = len(str(self.nStoredImages))
                fileName = f"{self.cameraConfig.GetFileName()}{str(self.imageCounter).zfill(paddingLength).self.cameraConfig.GetFileType()}"
                img.save(self.cameraConfig.GetOutputPath() + fileName);
                self.imageCounter += 1
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
