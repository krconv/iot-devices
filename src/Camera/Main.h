#include "../Common/Log.h"
#include "../Common/OtaUpdater.h"
#include "../Common/WifiClient.h"

namespace Camera
{

  class Main
  {
  public:
    Main()
        : wifiClient{},
          otaUpdater{wifiClient} {}

    void setup()
    {
      LOG_INIT();
      LOG("Starting up...");

      LOG("Setting up WiFi connection...");
      wifiClient.setup();
      LOG("Setting up OTA updates...");
      otaUpdater.setup();

      LOG("Successfully started.");
    }

    void loop()
    {
      wifiClient.loop();
      otaUpdater.loop();

      delay(10);
    }

  private:
    WifiClient wifiClient;
    OtaUpdater otaUpdater;
  };

} // namespace Camera
