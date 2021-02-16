# IoT Devices

This code powers various IoT devices set up at my house, including light switches and garage door sensors. The idea is that with all of the code in one place, sharing utilities between projects is easier.

## Setup

This project uses [PlatformIO](https://docs.platformio.org/en/latest/what-is-platformio.html), which manages the various dependencies and build configurations.

1.  [Install PlatformIO](https://docs.platformio.org/en/latest/core/installation.html)

## Building

To compile the entire project directly, use this command.

```sh
platformio run
```

Or, to compile the project for a specific configuration, use the `--environment` flag.

```sh
platformio run --environment office-light
```

To upload the project using Over-The-Air updates, use the `--target` flag.

```sh
platformio run --environment office-light --target upload
```
