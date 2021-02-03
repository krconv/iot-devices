#include "DeviceStatus.h"

#include <Arduino.h>

#include "../Common/Types.h"
#include "Configuration.h"

namespace LightSwitch
{

  DeviceStatus::DeviceStatus(const WifiClient &wifiClient_,
                             const MqttClient &mqttClient_)
      : wifiClient(wifiClient_),
        mqttClient(mqttClient_)
  {
  }

  void DeviceStatus::setup()
  {
    pinMode(Configuration::getButtonPin(), INPUT);
    bool buttonPressed = digitalRead(Configuration::getButtonPin()) == Configuration::getButtonVoltagePressed();
    if (buttonPressed)
    {
      safeMode = true;
      state = DeviceStatus::State::SAFE_MODE;
    }
  }

  void DeviceStatus::loop()
  {
    bool buttonPressed = digitalRead(Configuration::getButtonPin()) == Configuration::getButtonVoltagePressed();
    if (buttonPressed)
    {
      if (buttonPressStartedAt == 0)
      {
        buttonPressStartedAt = millis();
      }
      else if (millis() - buttonPressStartedAt > 5000)
      {
        restartStartedAt = millis();
        state = DeviceStatus::State::RESTARTING;
        buttonPressStartedAt = 0;
      }
    }
    else
    {
      buttonPressStartedAt = 0;
    }

    if (state == DeviceStatus::State::RESTARTING)
    {
      if (millis() - restartStartedAt > 5000)
      {
        ESP.reset();
      }
    }
    else if (!safeMode)
    {
      if (!wifiClient.isConnected() || !mqttClient.isConnected())
      {
        state = DeviceStatus::State::DISCONNECTED;
      }
      else
      {
        state = DeviceStatus::State::NORMAL;
      }
    }
  }

  DeviceStatus::State DeviceStatus::getState() const
  {
    return state;
  }

  bool DeviceStatus::isSafeMode() const
  {
    return safeMode;
  }

} // namespace LightSwitch
