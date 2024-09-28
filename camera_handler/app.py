from flask import Flask, render_template, Response
from camera_handler import CameraHandler
import io
import threading

cameraHandler = CameraHandler("./config/config.json")

app = Flask(__name__)

@app.route('/')
def index():
    return render_template("index.html")

def gen(cameraHandler):
    cameraHandler.Enable()
    while True:
        if cameraHandler.IsEnabled():
            img = cameraHandler.GetImage()
        else:
            img = cameraHandler.GetOfflineImage()

        img_io = io.BytesIO()
        img.save(img_io, 'JPEG')
        img_io.seek(0)

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + img_io.read() + b'\r\n\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(gen(cameraHandler),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

def runFlask():
    app.run(host='0.0.0.0', port=5000, debug=True, use_reloader=False)

if __name__ == '__main__':
    # Start Flask server thread
    flaskThread = threading.Thread(target=runFlask)
    flaskThread.daemon = True
    flaskThread.start()

    # Start MQTT handler thread
    mqttThread = threading.Thread(target=cameraHandler.StartMqtt)
    mqttThread.daemon = True
    mqttThread.start()

    flaskThread.join()
    mqttThread.join()

