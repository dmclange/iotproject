'use strict';

const express = require('express');
const path = require('path');
//mqtt
const mqtt = require('mqtt')
const host = 'test.mosquitto.org'
const port = '1883'
const clientId = `mqtt_${Math.random().toString(16).slice(3)}`
const connectUrl = `mqtt://${host}:${port}`
const client = mqtt.connect(connectUrl, {
  clientId,
  clean: true,
  connectTimeout: 4000,
  username: 'iotGroupProject',
  password: 'joseph',
  reconnectPeriod: 4000,
})

const app = express();
const floor_1_topic = '/building/floorone'; 
const floor_2_topic = '/building/floortwo'; 

app.listen(3000, () => {
    console.log("Application started and Listening on port 3000");
});
//tracks what profile we are on, and whether the lights are on or off
var profile_id = 0
var profile_status = 0

client.on('connect', () => {
    console.log('Connected')
    client.subscribe([floor_1_topic], () => {
      console.log(`Subscribe to topic '${floor_1_topic}'`)
    })
    client.subscribe([floor_2_topic], () => {
      console.log(`Subscribe to topic '${floor_2_topic}'`)
    })
})

app.post('/p1p', (req, res) => {
  console.log("p1p post");
  profile_id = 3
  profile_status = 1

  client.publish(floor_1_topic, '3', { qos: 0, retain: false }, (error) => {               
    if (error) {
      console.error(error)
    }
    console.log("sent 3");
  })
  res.sendStatus(201);
});

app.post('/p2p', (req, res) => {
  console.log("p2p post");
  profile_id = 4
  profile_status = 1

  client.publish(floor_2_topic, '4', { qos: 0, retain: false }, (error) => {               
    if (error) {
      console.error(error)
    }
  })
  res.sendStatus(201);
});

app.post('/p3p', (req, res) => {
  console.log("p3p post");
  profile_id = 5
  profile_status = 1

  client.publish(floor_1_topic, '5', { qos: 0, retain: false }, (error) => {               
    if (error) {
      console.error(error)
    }
  })
  res.sendStatus(201);
});

//serve index
app.use(express.static(__dirname));
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname + "/static/index.html"));
});

//double check mqtt was sent
client.on('message', (floor_1_topic, payload) => {
  console.log('Received Message:', floor_1_topic, payload.toString())
})

client.on('message', (floor_2_topic, payload) => {
  console.log('Received Message:', floor_2_topic, payload.toString())
})

//print local ipv4 address to console
var ip = require("ip");
console.dir ( ip.address() );

