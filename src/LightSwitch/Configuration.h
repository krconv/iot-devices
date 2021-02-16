#pragma once

#include <Arduino.h>
#include <string>

#include "../Common/Configuration.h"
#include "../Common/Types.h"
#include "../Setup.h"

namespace LightSwitch
{

  namespace Configuration
  {
    inline static pin_t getButtonPin()
    {
      return PIN_BUTTON;
    }

    constexpr inline static voltage_t getButtonVoltageNotPressed()
    {
      return VOLTAGE_BUTTON_NOT_PRESSED;
    }

    constexpr inline static voltage_t getButtonVoltagePressed()
    {
      return VOLTAGE_BUTTON_PRESSED;
    }

    inline static pin_t getRelayPin()
    {
      return PIN_RELAY;
    }

    constexpr inline static voltage_t getRelayVoltageOn()
    {
      return VOLTAGE_RELAY_ON;
    }

    constexpr inline static voltage_t getRelayVoltageOff()
    {
      return VOLTAGE_RELAY_OFF;
    }

    inline static pin_t getWhiteStatusLedPin()
    {
      return PIN_WHITE_STATUS_LED;
    }

    inline static pin_t getRedStatusLedPin()
    {
      return PIN_RED_STATUS_LED;
    }

    constexpr inline static analog_voltage_t getStatusLedVoltageOn()
    {
      return VOLTAGE_STATUS_LED_ON;
    }

    constexpr inline static analog_voltage_t getStatusLedVoltageDim()
    {
      return VOLTAGE_STATUS_LED_DIM;
    }

    constexpr inline static analog_voltage_t getStatusLedVoltageOff()
    {
      return VOLTAGE_STATUS_LED_OFF;
    }

    inline static std::string getMqttTopicButtonSetState()
    {
      return MQTT_DOMAIN "/" BUTTON_NAME "/state/set";
    }

    inline static std::string getMqttTopicButtonState()
    {
      return MQTT_DOMAIN "/" BUTTON_NAME "/state";
    }

    inline static std::string getMqttTopicSwitchSetState()
    {
      return MQTT_DOMAIN "/" SWITCH_NAME "/state/set";
    }

    inline static std::string getMqttTopicSwitchState()
    {
      return MQTT_DOMAIN "/" SWITCH_NAME "/state";
    }

    inline static std::string getMqttPayloadOn()
    {
      return "on";
    }

    inline static std::string getMqttPayloadOff()
    {
      return "off";
    }

  } // namespace Configuration

} // namespace LightSwitch
