#include "OtaUpdater.h"

#include <ArduinoOTA.h>

#include "Configuration.h"

OtaUpdater::OtaUpdater(const WifiClient &wifiClient_)
    : wifiClient(wifiClient_) {}

void OtaUpdater::setup()
{
  ArduinoOTA.setHostname(Configuration::getId().c_str());
}

void OtaUpdater::loop()
{
  if (wifiClient.isConnected())
  {
    ArduinoOTA.begin(true);
    ArduinoOTA.handle();
  }
}
