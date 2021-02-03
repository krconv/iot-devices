# IoT Devices

This code powers various IoT devices set up at my house, including light switches and garage door sensors. The idea is that with all of the code in one place, sharing utilities between projects is easier.

## Setup

I've used the [`arduino-cli`](https://arduino.github.io/arduino-cli/latest/) for getting things set up locally. With that installed, use these commands to install the required dependencies.

```sh
arduino-cli lib install ArduinoOTA@1.0.5
arduino-cli lib install PubSubClient@2.8.0
```

## Building

To compile the project directly, use this command.

```sh
arduino-cli compile --fqbn esp8266:esp8266:generic .
```

Or, use `make` to build and upload the project.

```sh
make upload DEVICE=LIVING_ROOM_OUTLETS
```
