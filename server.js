const express = require("express");
const mqtt = require("mqtt");
const path = require("path");
require("dotenv").config(); 

const app = express();
const PORT = process.env.PORT;  
const MQTT_BROKER = process.env.MQTT_BROKER;

const client = mqtt.connect(MQTT_BROKER);
client.on("connect", () => {
  console.log(`Connected to MQTT Broker at ${MQTT_BROKER}`);
});

app.use(express.static(__dirname));

app.use((req, res, next) => {
  console.log(`Request received: ${req.method} ${req.url}`);
  next();
});

app.get("/setColor", (req, res) => {
  console.log("Handling /setColor request...");

  const led = req.query.led;
  let color = req.query.color;

  if (led && color) {
    color = decodeURIComponent(color);
    const topic = `led/${led}/color`;

    console.log(`Publishing ${color} to ${topic}`);
    client.publish(topic, color);
    res.send("Color updated successfully!");
  } else {
    console.log("Invalid request!");
    res.status(400).send("Invalid request");
  }
});

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "index.html"));
});

app.listen(PORT, "0.0.0.0", () => console.log(`Server running at http://192.168.3.126:${PORT}`));
