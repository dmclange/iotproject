#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Daniel Lange"
__version__ = "0.1.0"
__license__ = "MIT"

import paho.mqtt.client as mqtt
import mariadb, sys, re, queue

def on_connect(client, userdata, flags, rc):
    # subscribing to topic so we know when to check database for updoots
    client.subscribe("database/+/update")

def on_message(client, userdata, msg):
    # first put everything in a queue so messages can not get fragmented
    q = queue.Queue()
    q.put((msg.topic,msg.payload))
    current = q.get()
    id = re.findall(r"/\d/",current[0])
    id = id[0].replace('/','')
    publishActuator(client,id)


def publishActuator(client, iid):
    try:
        conn = mariadb.connect(
            user="app",
            password="supersecurepassword",
            host="localhost",
            port=3306,
            database="appdb"
        )

    except mariadb.Error as e:
        print(f"Error connecting to DB: {e}")
        sys.exit(1)
    cur = conn.cursor()
    cur.execute(
            "SELECT id,state,color,intensity FROM actuators WHERE id=" + iid + ";"
            )
    for (id,state,color,intensity) in cur:
        pubtop = "actuators/"+id+"/state"
        client.publish(topic=pubtop,payload=state)
        pubtop = "actuators/"+id+"/color"
        client.publish(topic=pubtop,payload=color)
        pubtop = "actuators/"+id+"/intensity"
        client.publish(topic=pubtop,payload=intensity)
    conn.close()

def main():
    client = mqtt.Client()
    client.connect("localhost", 1883, 60)
    client.on_connect = on_connect
    client.on_message = on_message
    client.loop_forever() 

if __name__ == "__main__":
    main()