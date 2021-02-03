#include "StatusLed.h"

#include "Configuration.h"

namespace LightSwitch
{

  StatusLed::StatusLed(pin_t pin_, analog_voltage_t voltageOn_, analog_voltage_t voltageOff_)
      : pin(pin_),
        voltageOn(voltageOn_),
        voltageOff(voltageOff_) {}

  void StatusLed::setup()
  {
    pinMode(pin, OUTPUT);
    analogWrite(pin, voltageOff);
  }

  void StatusLed::loop()
  {
    switch (state)
    {
    case StatusLed::LedState::ON:
      analogWrite(pin, voltageOn);
      break;
    case StatusLed::LedState::OFF:
      analogWrite(pin, voltageOff);
      break;
    case StatusLed::LedState::BLINKING:
      bool isOn = (blinkStart - millis()) / 500 % 2;
      analogWrite(pin, isOn ? voltageOn : voltageOff);
      break;
    }
  }

  void StatusLed::setState(LedState ledState)
  {
    if (state == ledState || ledState == StatusLed::LedState::NONE)
    {
      return;
    }

    state = ledState;
    if (state == StatusLed::LedState::BLINKING)
    {
      blinkStart = millis();
    }
    else
    {
      blinkStart = 0;
    }
  }

} // namespace LightSwitch
