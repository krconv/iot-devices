#include "StatusLeds.h"

#include "Configuration.h"

namespace LightSwitch
{

  StatusLeds::StatusLeds(const DeviceStatus &deviceStatus_,
                         const Button &button_)
      : deviceStatus(deviceStatus_),
        button(button_),
        whiteLed{Configuration::getWhiteStatusLedPin(), Configuration::getStatusLedVoltageOn(), Configuration::getStatusLedVoltageDim()},
        redLed{Configuration::getRedStatusLedPin(), Configuration::getStatusLedVoltageOn(), Configuration::getStatusLedVoltageOff()}
  {
  }

  void StatusLeds::setup()
  {
    whiteLed.setup();
    redLed.setup();
  }

  void StatusLeds::loop()
  {
    switch (button.getState())
    {
    case Button::State::ON:
      whiteLed.setState(StatusLed::LedState::ON);
      break;
    case Button::State::OFF:
      whiteLed.setState(StatusLed::LedState::OFF);
      break;
    default:
      break;
    }

    switch (deviceStatus.getState())
    {
    case DeviceStatus::State::SAFE_MODE:
      redLed.setState(StatusLed::LedState::ON);
      break;
    case DeviceStatus::State::RESTARTING:
    case DeviceStatus::State::DISCONNECTED:
      redLed.setState(StatusLed::LedState::BLINKING);
      break;
    default:
      redLed.setState(StatusLed::LedState::OFF);
      break;
    }

    whiteLed.loop();
    redLed.loop();
  }

} // namespace LightSwitch
