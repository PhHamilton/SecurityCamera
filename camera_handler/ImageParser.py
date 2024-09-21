import datetime
from PIL import Image, ImageDraw, ImageFont

class ImageParser(object):
    def __init__(self):
        self.padding_x = 10
        self.padding_y = self.padding_x

    def AddTimestamp(self, frame, color=(255, 255 ,255)):
        current_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        img = Image.fromarray(frame).convert('RGB')  # Ensures it is in RGB format
        (text_width, text_height) = self.GetTextSize(img, current_time)
        x = img.width - text_width - self.padding_x
        y = img.height - text_height - self.padding_y

        return self.DrawOnImage(img, current_time, (x, y))

    def AddCPUTemp(self, img, color=(255, 255 ,255)):
        f = open("/sys/class/thermal/thermal_zone0/temp", "r")
        temp = round(float(f.readline())/1000, 2)
        temp = "Camera Temperature: " + str(temp) + " °C"

        (text_width, text_height) = self.GetTextSize(img, temp)
        x = self.padding_x
        y = self.padding_y

        return self.DrawOnImage(img, temp, (x, y))

        pass

    def DrawOnImage(self, img, txt, pos, color=(255, 255 ,255)):
        draw = ImageDraw.Draw(img)
        font = ImageFont.load_default()
        draw.text(pos, txt, font=font, fill=color)
        return img

    def GetTextSize(self, img, txt):
         return ImageDraw.Draw(img).textsize(txt)
