from PIL import Image, ImageDraw, ImageFont

class ImageDrawer(object):
    def DrawOnImage(self, img, txt, pos, color=(255, 255 ,255)):
        draw = ImageDraw.Draw(img)
        font = ImageFont.load_default()
        draw.text(pos, text, font=font, fill=color)

        return img
