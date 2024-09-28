from picamera2 import Picamera2
from PIL import Image

class Camera(object):
    def __init__(self, flip=False, fileType=".jpg", imageName="img_"):
        self.flip = flip
        self.fileType = fileType
        self.imageName = imageName
        self.tuning = Picamera2.load_tuning_file("imx219_noir.json");
        self.camera = Picamera2(tuning = self.tuning)  # Fixed to Picamera2
        self.CameraEnabled = False
        self.UnavailableImage = Image.open("./placeholders/CameraNotAvailable.jpg")

    def __del__(self):
        self.camera.stop()
        self.camera.close();

    def GetFrame(self):
        frame = self.camera.capture_array()
        return frame

    def GetOfflineFrame(self):
        return Image.fromarray(self.UnavailableImage)

    def TakePicture(self):
        pass

    def Enable(self):
        self.camera.stop()
        self.camera.configure(self.camera.create_video_configuration(main={"size": (1280, 720), "format": "RGB888"}, controls={"FrameRate": 15}))
        self.camera.start()
        self.CameraEnabled = True

    def Disable(self):
        self.camera.stop()
        self.camera.configure(self.camera.create_still_configuration(main={"size": (640, 480), "format": "RGB888"}))
        self.camera.start()
        self.CameraEnabled = False

    def IsEnabled(self):
        return self.CameraEnabled
