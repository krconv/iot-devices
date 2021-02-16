#include <Arduino.h>

#include "Setup.h"

#if DEVICE_CLASS == DEVICE_CLASS__LIGHT_SWITCH
#include "LightSwitch/Main.h"
static LightSwitch::Main LIGHT_SWITCH{};
#endif

#if DEVICE_CLASS == DEVICE_CLASS__CAMERA
#include "Camera/Main.h"
static Camera::Main CAMERA{};
#endif

void setup()
{
#if DEVICE_CLASS == DEVICE_CLASS__LIGHT_SWITCH
  LIGHT_SWITCH.setup();
#endif

#if DEVICE_CLASS == DEVICE_CLASS__CAMERA
  CAMERA.setup();
#endif
}

void loop()
{
#if DEVICE_CLASS == DEVICE_CLASS__LIGHT_SWITCH
  LIGHT_SWITCH.loop();
#endif

#if DEVICE_CLASS == DEVICE_CLASS__CAMERA
  CAMERA.loop();
#endif
}
