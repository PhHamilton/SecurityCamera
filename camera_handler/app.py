# app.py

from flask import Flask, render_template, Response
from mqtt_handler import MQTTHandler
from camera import Camera as camera
from ImageParser import ImageParser
import io
import threading
from camera_handler import CameraHandler

imgParser = ImageParser()
cameraHandler = CameraHandler("./config/config.json");

app = Flask(__name__)

@app.route('/')
def index():
    return render_template("index.html")

#def gen(camera):
#    camera.Enable()
#    while True:
#        if(camera.IsEnabled()):
#            frame = camera.GetFrame()
#            img = imgParser.AddTimestamp(frame)
#            img = imgParser.AddCPUTemp(img)
#        else:
#            img = camera.GetOfflineFrame()
#        img_io = io.BytesIO()
#        img.save(img_io, 'JPEG')
#        img_io.seek(0)
#
#        yield (b'--frame\r\n'
#               b'Content-Type: image/jpeg\r\n\r\n' + img_io.read() + b'\r\n\r\n')

def gen(camera):
    cameraHandler.Enable()
    while True:
        if(cameraHandler.IsEnabled()):
            img = cameraHandler.GetImage();
        else:
            return;
            #img = cameraHandler.GetOfflineFrame()
        img_io = io.BytesIO()
        img.save(img_io, 'JPEG')
        img_io.seek(0)

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + img_io.read() + b'\r\n\r\n')
@app.route('/video_feed')
def video_feed():
    return Response(gen(camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')
def runFlask():
    app.run(host='0.0.0.0', port=5000, debug = True, use_reloader=False)

if __name__ == '__main__':
    flaskThread = threading.Thread(target = runFlask);
    flaskThread.daemon = True;
    flaskThread.start();

    mqttThread = threading.Thread(target = cameraHandler.StartMqtt);
    mqttThread.daemon = True;
    mqttThread.start();

    flaskThread.join()

