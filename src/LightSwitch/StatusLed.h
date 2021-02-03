#pragma once

#include "../Common/Types.h"

namespace LightSwitch
{

  class StatusLed
  {
  public:
    enum struct LedState
    {
      NONE,
      OFF,
      ON,
      BLINKING
    };

  public:
    StatusLed(pin_t pin_, analog_voltage_t voltageOn_, analog_voltage_t voltageOff_);

    void setup();
    void loop();

    void setState(LedState ledState);

  private:
    const pin_t pin;
    const analog_voltage_t voltageOn;
    const analog_voltage_t voltageOff;

    LedState state = LedState::OFF;
    millis_t blinkStart = 0;
  };

} // namespace LightSwitch
