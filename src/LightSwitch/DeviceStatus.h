#pragma once

#include "../Common/WifiClient.h"
#include "../Common/MqttClient.h"

namespace LightSwitch
{

  class DeviceStatus
  {
  public:
    enum struct State
    {
      NONE,
      DISCONNECTED,
      SAFE_MODE,
      RESTARTING,
      NORMAL
    };

  public:
    DeviceStatus(const WifiClient &wifiClient_,
                 const MqttClient &mqttClient_);

    void setup();
    void loop();

    bool isSafeMode() const;
    State getState() const;

  private:
    const WifiClient &wifiClient;
    const MqttClient &mqttClient;

    State state = State::NONE;
    bool safeMode = false;
    millis_t buttonPressStartedAt = 0;
    millis_t restartStartedAt = 0;
  };

} // namespace LightSwitch
