from picamera2 import Picamera2
from PIL import Image

class Camera(object):
    def __init__(self, flip=False, fileType=".jpg", imageName="img_"):
        self.flip = flip
        self.fileType = fileType
        self.imageName = imageName
        self.CameraEnabled = False
        self.camera = None  # Initialized as None to prevent early initialization
        self.UnavailableImage = Image.open("./placeholders/CameraNotAvailable.jpg")

    def __del__(self):
        self.Disable()  # Ensure camera is properly closed on object destruction

    def GetFrame(self):
        if self.camera:
            return self.camera.capture_array()
        else:
            return self.UnavailableImage

    def GetOfflineFrame(self):
        return Image.fromarray(self.UnavailableImage)

    def Enable(self):
        if not self.CameraEnabled:
            if not self.camera:
                self.tuning = Picamera2.load_tuning_file("imx219_noir.json")
                self.camera = Picamera2(tuning=self.tuning)
            self.camera.configure(self.camera.create_video_configuration(main={"size": (1280, 720), "format": "RGB888"}, controls={"FrameRate": 15}))
            self.camera.start()
            self.CameraEnabled = True

    def Disable(self):
        if self.CameraEnabled and self.camera:
            self.camera.stop()
            self.camera.close()
            self.camera = None  # Ensure the camera is fully released
            self.CameraEnabled = False

    def IsEnabled(self):
        return self.CameraEnabled

