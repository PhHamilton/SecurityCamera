import paho.mqtt.client as mqtt
from config_handler import ConfigHandler

class MQTTHandler(object):
    def __init__(self, filePath):
        self.config = ConfigHandler(filePath);
        self.client = mqtt.Client();
        self.client.on_connect = self.OnConnect;
        self.client.on_message = self.OnMessage;
        self.client.on_publish = self.OnPublish;
        self.IsRunning = False

    def StartMQTT(self):
        self.IsRunning = True
        self.client.connect(self.config.GetAddress(),
                            self.config.GetPort(),
                            self.config.GetKeepAlive()
                           )

        #self.client.loop_forever();
        self.client.loop_start()
        while(self.IsRunning):
            pass
        self.client.loop_stop()
        self.client.disconnect();

    def StopMQTT(self):
        self.IsRunning = False

    def PublishMessage(self, topic, payload):
        self.client.publish(topic, payload)

    def OnConnect(self, client, userdata, flags, rc):
        if rc == 0:
            print("Connected to broker successfully!")
            # Subscribe to a topic
            client.subscribe(self.config.GetSubscriptionTopics())
        else:
            print(f"Failed to connect, return code {rc}")

    # Callback function when a message is received
    def OnMessage(self, client, userdata, msg):
        print(f"Message received: {msg.payload.decode()} from topic: {msg.topic}")

    # Callback function when a message is published
    def OnPublish(self, client, userdata, mid):
        print(f"Message published with mid: {mid}")

if __name__ == "__main__":
    mqttHandler = MQTTHandler("./config/config.json");
    mqttHandler.StartMQTT()
