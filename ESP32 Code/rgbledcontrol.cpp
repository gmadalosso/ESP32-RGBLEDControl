#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const char* mqtt_server = "MQTT_SERVER_IP";

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    while (!client.connected()) {
        if (client.connect("ESP32Client")) {
            client.subscribe("led/+/color");
        } else {
            delay(2000);
        }
    }

    pwm.begin();
    pwm.setPWMFreq(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
    String color = "";
    for (int i = 0; i < length; i++) {
        color += (char)payload[i];
    }

    int ledNumber = extractLedNumber(topic);
    int r, g, b;
    
    if (parseHexColor(color, r, g, b)) {
        setColor(ledNumber, r, g, b);
    }
}

int extractLedNumber(String topic) {
    int firstSlash = topic.indexOf("/") + 1;
    int secondSlash = topic.indexOf("/", firstSlash);
    return topic.substring(firstSlash, secondSlash).toInt();
}

bool parseHexColor(String hex, int &r, int &g, int &b) {
    if (hex.charAt(0) == '#' && hex.length() == 7) {
        r = strtol(hex.substring(1, 3).c_str(), NULL, 16);
        g = strtol(hex.substring(3, 5).c_str(), NULL, 16);
        b = strtol(hex.substring(5, 7).c_str(), NULL, 16);
        return true;
    }
    return false;
}

void setColor(int led, int r, int g, int b) {
    int redPin = led * 3;
    int greenPin = redPin + 1;
    int bluePin = redPin + 2;

    pwm.setPWM(redPin, 0, map(r, 0, 255, 0, 4095));
    pwm.setPWM(greenPin, 0, map(g, 0, 255, 0, 4095));
    pwm.setPWM(bluePin, 0, map(b, 0, 255, 0, 4095));
}

void loop() {
    client.loop();
}
