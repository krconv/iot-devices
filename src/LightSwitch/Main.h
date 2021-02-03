#include "../Common/Log.h"
#include "../Common/MqttClient.h"
#include "../Common/OtaUpdater.h"
#include "../Common/WifiClient.h"
#include "Button.h"
#include "DeviceStatus.h"
#include "StatusLeds.h"
#include "Switch.h"

namespace LightSwitch
{

  class Main
  {
  public:
    Main()
        : wifiClient{},
          otaUpdater{wifiClient},
          mqttClient{wifiClient},
          button{mqttClient},
          lightSwitch{mqttClient},
          deviceStatus{wifiClient, mqttClient},
          statusLeds{deviceStatus, button} {}

    void setup()
    {
      LOG_INIT();
      LOG("Starting up...");

      LOG("Setting up WiFi connection...");
      wifiClient.setup();
      LOG("Setting up OTA updates...");
      otaUpdater.setup();

      deviceStatus.setup();
      if (deviceStatus.isSafeMode())
      {
        LOG("Running in safe mode.");
      }
      else
      {
        LOG("Setting up MQTT connection...");
        mqttClient.setup();

        button.setup();
        lightSwitch.setup();
      }
      statusLeds.setup();
      LOG("Successfully started.");
    }

    void loop()
    {
      wifiClient.loop();
      otaUpdater.loop();

      deviceStatus.loop();
      if (!deviceStatus.isSafeMode())
      {
        mqttClient.loop();

        button.loop();
        lightSwitch.loop();
      }
      statusLeds.loop();

      delay(10);
    }

  private:
    WifiClient wifiClient;
    OtaUpdater otaUpdater;

    MqttClient mqttClient;

    Button button;
    Switch lightSwitch;

    DeviceStatus deviceStatus;
    StatusLeds statusLeds;
  };

} // namespace LightSwitch
