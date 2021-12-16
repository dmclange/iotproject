'use strict';

const express = require('express');
const path = require('path');
const mqtt = require('mqtt')
//mosquitto test is placeholder
const client = mqtt.connect('https://test.mosquitto.org/')

const app = express();

app.listen(3000, () => {
    console.log("Application started and Listening on port 3000");
});
//tracks what profile we are on, and whether the lights are on or off
var profile_id = 0
var profile_status = 0

app.post('/p1p', (req, res) => {
    console.log("p1p post");

    client.on('connect', () => {
    	client.publish('building/1/connected', 'true')
    })
    profile_id = 1
    profile_status = 1
    res.sendStatus(201);
});
app.post('/p2p', (req, res) => {
    console.log("p2p post");

    profile_id = 2
    profile_status = 1
    res.sendStatus(201);
});

app.post('/p3p', (req, res) => {
    console.log("p3p post");

    profile_id = 3
    profile_status = 1
    res.sendStatus(201);
});

//serve index
app.use(express.static(__dirname));
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname + "/static/index.html"));
});

var ip = require("ip");
console.dir ( ip.address() );

