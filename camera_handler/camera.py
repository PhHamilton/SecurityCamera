from picamera2 import Picamera2
from PIL import Image

class Camera(object):
    def __init__(self, cameraConfig):
        self.cameraConfig = cameraConfig;
        self.camera = None
        self.UnavailableImage = Image.open("./placeholders/CameraNotAvailable.jpg")
        self.cameraEnabled = False
    def __del__(self):
        self.Disable()

    def GetFrame(self):
        if self.camera:
            return self.camera.capture_array()
        else:
            return self.UnavailableImage

    def GetOfflineFrame(self):
        return Image.fromarray(self.UnavailableImage)

    def Enable(self):
        if not self.cameraEnabled:
            if not self.camera:
                self.tuning = Picamera2.load_tuning_file("imx219_noir.json")
                self.camera = Picamera2(tuning=self.tuning)
            self.camera.configure(self.camera.create_video_configuration(main={"size": self.cameraConfig.GetResolution(), "format": "RGB888"}, controls={"FrameRate": self.cameraConfig.GetFrameRate()}))
            self.camera.start()
            self.cameraEnabled = True

    def Disable(self):
        if self.cameraEnabled and self.camera:
            self.camera.stop()
            self.camera.close()
            self.camera = None  # Ensure the camera is fully released
            self.cameraEnabled = False

    def IsEnabled(self):
        return self.cameraEnabled

