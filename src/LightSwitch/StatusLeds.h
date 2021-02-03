#pragma once

#include "../Common/Types.h"
#include "Button.h"
#include "DeviceStatus.h"
#include "StatusLed.h"

namespace LightSwitch
{

  class StatusLeds
  {
  public:
    StatusLeds(const DeviceStatus &deviceStatus_, const Button &button_);

    void setup();
    void loop();

  private:
    const DeviceStatus &deviceStatus;
    const Button &button;

    StatusLed whiteLed;
    StatusLed redLed;
  };

} // namespace LightSwitch
