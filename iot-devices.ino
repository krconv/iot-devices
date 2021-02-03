#include "src/Setup.h"

#if DEVICE_CLASS == DEVICE_CLASS__LIGHT_SWITCH
#include "src/LightSwitch/Main.h"
static LightSwitch::Main LIGHT_SWITCH{};
#endif

void setup()
{
#if DEVICE_CLASS == DEVICE_CLASS__LIGHT_SWITCH
  LIGHT_SWITCH.setup();
#endif
}

void loop()
{
#if DEVICE_CLASS == DEVICE_CLASS__LIGHT_SWITCH
  LIGHT_SWITCH.loop();
#endif
}
