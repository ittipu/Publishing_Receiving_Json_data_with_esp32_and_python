from config import *
import paho.mqtt.client as mqtt
import time
import datetime
import json


client = mqtt.Client(protocol=mqtt.MQTTv311)


message = dict()
year_now = datetime.datetime.now()
month_now = datetime.datetime.now()
day_now = datetime.datetime.now()

def on_connect(client, userdata, flags, rc):
    print("Result from connect: {}".format(mqtt.connack_string(rc)))

client.connect(host=mqtt_server_host, port=mqtt_server_port, keepalive=mqtt_keepalive)

while True:

    timestamp = time.time().__round__()
    message["timestamp"] = timestamp.__str__()
    message["day"] = day_now.day
    message["month"] = month_now.month
    message["year"] = year_now.year
    message_json = json.dumps(message)
    print("Message: {}".format(message_json))
    client.publish("esp/light", message_json)
    time.sleep(3)
