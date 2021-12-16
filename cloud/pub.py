#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Daniel Lange"
__version__ = "0.1.0"
__license__ = "MIT"

import paho.mqtt.client as mqtt
import mariadb, sys

client = mqtt.Client()
prevState = 0
def publishActuator(id):
    global prevState
    try:
        conn = mariadb.connect(
            user="app",
            password="supersecurepassword",
            host="localhost",
            port="3306",
            database="appdb"
        )

    except mariadb.Error as e:
        print(f"Error connecting to DB: {e}")
        sys.exit(1)
    cur = conn.cursor()
    try:
        cur.execute(
            "SELECT id,state,color,intensity FROM actuators WHERE id=" + id + ";"
            )
        if (prevState != cur.state):
            for (id,state,color,intensity) in cur:
                pubtop = "actuators/"+id+"/state"
                client.publish(topic=pubtop,payload=state)
                pubtop = "actuators/"+id+"/color"
                client.publish(topic=pubtop,payload=color)
                pubtop = "actuators/"+id+"/intensity"
                client.publish(topic=pubtop,payload=intensity)
                prevState = cur.state
    except mariadb.Error as e:
        print(f"Error: {e}")
    conn.close()

def main():
    global client
    client.connect("192.168.141.247", 1883, 60)
    while True:
        print("lol\n")

if __name__ == "__main__":
    main()