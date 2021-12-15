#!/usr/bin/env python3
"""
Module Docstring
"""

__author__ = "Daniel Lange"
__version__ = "0.1.0"
__license__ = "MIT"

import paho.mqtt.client as mqtt
import mariadb
import sys, queue, re

def writeDB(query):
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
    client.subscribe([("actuators/+/color",0), ("actuators/+/intensity",0), ("actuators/+/state",0), ("sensors/+/lightlevel",0), ("sensors/+/temp",0)])

def on_message(client, userdata, msg):
    q = queue.Queue()
    q.put((msg.topic,msg.payload))
    current = q.get()
    payload = current[1]
    id = re.findall(r"/\d/",current[0])
    id = id[0].replace('/','')
    kvp = current[0].split("/")
    table = kvp[0]
    value = kvp[2]
    decoded = payload.decode('utf8')
    print("Testing printing")
    query = 'UPDATE '+ table +' SET '+ value +' = ' + decoded + ' WHERE id = ' + id + ';'
    writeDB(query)

def main():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("localhost", 1883, 60)
    client.loop_forever()


if __name__ == "__main__":
    main()
