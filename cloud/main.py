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

def on_connect(client, userdata, flags, rc):
    client.subscribe("idontknow")

def on_message(client, userdata, msg):
    cursor

def startClient(url):
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    try:
        client.connect(url, 1883, 60)
    except mqtt.MQTT_ERR_CONN_REFUSED as e:
        print(f"MQTT connection refused: {e}")
        sys.exit(1)

def connectDB():
    try:
        conn = mariadb.connect(
            user="appuser",
            password="supersecurepassword"
            host="localhost"
            port="3306"
            database="appdb"
        )
    except mariadb.Error as e:
        print(f"Error connecting to DB: {e}")
        sys.exit(1)
    cur = conn.cursor()
    cur.execute(
        "ENTER QUERY HERE"
    )
    
    
def main():
    startClient("joes.mqtt.broker")

if __name__ == "__main__":
    main()