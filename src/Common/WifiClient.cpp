#include "WifiClient.h"

#include "Configuration.h"

WifiClient::WifiClient()
    : client(WiFiClient()) {}

void WifiClient::setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(Configuration::getWifiSsid().c_str(),
             Configuration::getWifiPassword().c_str());
}

void WifiClient::loop()
{
  lastKnownStatus = WiFi.status();
}

WiFiClient &WifiClient::getClient()
{
  return client;
}

bool WifiClient::isConnected() const
{
  return lastKnownStatus == WL_CONNECTED;
}
