#!/usr/bin/env python
import time
from std_msgs.msg import String
import paho.mqtt.client as mqtt
import rospy



MQTT_server = "192.168.1.111"



      
# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("/mqtt_trigger")
   
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    if msg.topic=="/mqtt_trigger":
        data =str(msg.payload)
        if (data == "attention" or data =="thinking" or data =="weather" or data=="thankyou" or data =="group_greeting" or data =="hello" or data =="move_neck")
		pub.publish(data)     
	if (data== "intro" or data == "intro_movement")
		intro_pub.publish(data)

pub = rospy.Publisher('/pose_name', String, queue_size=100)
intro_pub = rospy.Publisher('/intro_pose', String, queue_size=100)
rospy.init_node('trigger_catcher_mqtt')
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(MQTT_server, 1883, 90)

