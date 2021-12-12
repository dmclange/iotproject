#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Daniel Lange"
__version__ = "0.1.0"
__license__ = "MIT"

import paho.mqtt.client as mqtt
import mariadb
import sys

def writeDB(query):
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
            query
            )
    except mariadb.Error as e:
        print(f"Error: {e}")
    conn.commit()
    print("Ran "+query)
    conn.close()

def on_connect(client, userdata, flags, rc):
    client.subscribe("building/+/room/+/light/+/profile/+/timezone/+/lightstatus/+",0)

def on_message(client, userdata, msg):
    actuatorid = ""
    query = ""
    decoded = str(msg.payload.decode("utf-8"))
    query = "UPDATE appdb.actuators SET state = " + decoded + "WHERE id = " + actuatorid + ";"
    writeDB(query)

def main():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("test.mosquitto.org", 1883, 60)
    client.loop_forever()

if __name__ == "__main__":
    main()