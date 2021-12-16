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

# writing to database
def writeDB(query):
    try:
        # establishing connection
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
        # executing query
        cur.execute(
            query
            )
    except mariadb.Error as e:
        print(f"Error: {e}")
    # committing changes
    conn.commit()
    # closing connection
    conn.close()

def on_connect(client, userdata, flags, rc):
    # subscribing to topics
    client.subscribe([("actuators/+/color",0), ("actuators/+/intensity",0), ("actuators/+/state",0), ("sensors/+/lightlevel",0), ("sensors/+/temp",0)])

def on_message(client, userdata, msg):
    # put the received message in a queue so that we don't process partial messages
    q = queue.Queue()
    q.put((msg.topic,msg.payload))
    # getting the first message in queue
    current = q.get()
    payload = current[1]
    # finding id of item by regex (in the future maybe different handling based on topic)
    id = re.findall(r"/\d/",current[0])
    id = id[0].replace('/','')
    # time to construct the query to update the database
    kvp = current[0].split("/")
    table = kvp[0]
    value = kvp[2]
    decoded = payload.decode('utf8')
    query = 'UPDATE '+ table +' SET '+ value +' = ' + decoded + ' WHERE id = ' + id + ';'
    # run query
    writeDB(query)

def main():
    # establishing mqtt client and running it in a loop
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("localhost", 1883, 60)
    client.loop_forever()


if __name__ == "__main__":
    main()