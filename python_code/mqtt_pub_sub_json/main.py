from config import *
import paho.mqtt.client as mqtt
import json


def on_connect(client, userdata, flags, rc):
    print("Result from connect: {}".format(mqtt.connack_string(rc)))
    client.subscribe("esp/test")


def on_subscribe(client, userdata, mid, granted_qos):
    print("I've subscribe with QoS: {}".format(granted_qos[0]))


def on_message(client, userdata, msg):
    topic = msg.topic
    m_decode = str(msg.payload.decode("utf-8", "ignore"))
    m_in = json.loads(m_decode)
    print("Topic: ", topic)
    print("Message: ", m_in)


if __name__ == "__main__":
    client = mqtt.Client(protocol=mqtt.MQTTv311)
    client.on_connect = on_connect
    client.on_subscribe = on_subscribe
    client.on_message = on_message

    client.connect(host=mqtt_server_host, port=mqtt_server_port, keepalive=mqtt_keepalive)
    client.loop_forever()


