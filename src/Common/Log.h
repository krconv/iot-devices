#pragma once

#include <HardwareSerial.h>
#include <strings.h>

#define LOG_INIT() Serial.begin(115200)

#define LOG_F(message, ...)                     \
  Serial.printf("[%6.3f] ", millis() / 1000.0); \
  Serial.printf(message, __VA_ARGS__);          \
  Serial.println()

#define LOG(message)                            \
  Serial.printf("[%6.3f] ", millis() / 1000.0); \
  Serial.println(message)
