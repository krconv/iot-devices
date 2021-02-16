#include "OtaUpdater.h"

#include <ArduinoOTA.h>

#include "Configuration.h"

OtaUpdater::OtaUpdater(const WifiClient &wifiClient_)
    : wifiClient(wifiClient_) {}

void OtaUpdater::setup()
{
#ifdef ESP8266
  ArduinoOTA.begin(Configuration::getId().c_str());
#else
  ArduinoOTA.setHostname(Configuration::getId().c_str());
#endif
}

void OtaUpdater::loop()
{
  if (wifiClient.isConnected())
  {
#ifdef ESP8266
    ArduinoOTA.begin(true);
#else
    ArduinoOTA.begin();
#endif
    ArduinoOTA.handle();
  }
}
