#!/usr/bin/env python
import time
from std_msgs.msg import String
import paho.mqtt.client as mqtt
import rospy

data=""

MQTT_server = "192.168.1.111"


# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("/mqtt_trigger",2)
   
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print("message received")	
    if msg.topic=="/mqtt_trigger":
        data =str(msg.payload)
	print(data)
	pub.publish(data)
	intro_pub.publish(data)
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(MQTT_server, 1883, 90)
rospy.init_node('trigger_catcher_mqtt')
pub = rospy.Publisher('/pose_name', String, queue_size=100)
intro_pub = rospy.Publisher('/intro_pose', String, queue_size=100)


while (1):
	client.loop_start()
	
	client.loop_stop()

