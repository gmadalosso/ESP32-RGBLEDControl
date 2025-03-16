# Web App to control RGB LEDs using an ESP32 and a PCA9685 PWM Driver

This is a simple project that shows how to control RGB LEDs using an ESP32 + PCA9685 PWM Driver, a web interface, and MQTT communication via a Mosquitto broker. The ESP32 receives color change commands from a web page and updates the LED colors accordingly.

## How It Works

- A **web page** lets users pick colors for each LED.
- The **Node.js backend** receives color updates and publishes MQTT messages.
- The **Mosquitto broker** forwards messages to the ESP32.
- The **ESP32 reads the messages** and adjusts the RGB LEDs via PWM through the PCA9685 driver.

## Blog Post

For a full explanation of this project, including pictures and videos of the project working, check out the blog post:

👉 [Read the full article here](https://gmadalosso.hashnode.dev/project-web-app-to-control-rgb-leds-using-an-esp32-and-a-pca9685-pwm-driver)
