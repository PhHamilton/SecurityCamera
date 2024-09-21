# app.py

from flask import Flask, render_template, Response
from camera_handler import CameraHandler as camera
from ImageParser import ImageParser
import io

imgParser = ImageParser()

app = Flask(__name__)

@app.route('/')
def index():
    return render_template("index.html")

def gen(camera):
    camera.Enable()
    while True:
        if(camera.IsEnabled()):
            frame = camera.GetFrame()
            img = imgParser.AddTimestamp(frame)
            img = imgParser.AddCPUTemp(img)
        else:
            img = camera.GetOfflineFrame()
        img_io = io.BytesIO()
        img.save(img_io, 'JPEG')
        img_io.seek(0)

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + img_io.read() + b'\r\n\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(gen(camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)

