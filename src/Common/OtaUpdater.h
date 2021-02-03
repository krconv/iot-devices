#pragma once

#include "WifiClient.h"

class OtaUpdater
{
public:
  OtaUpdater(const WifiClient &wifiClient_);

  void setup();
  void loop();

private:
  const WifiClient &wifiClient;
};
