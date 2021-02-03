#include "Button.h"

#include <functional>

#include <Arduino.h>

#include "Configuration.h"

namespace LightSwitch
{

  Button::Button(MqttClient &mqttClient_)
      : mqttClient(mqttClient_)
  {
  }

  void Button::setup()
  {
    pinMode(Configuration::getButtonPin(), INPUT);

    mqttClient.subscribe(
        Configuration::getMqttTopicButtonState(),
        std::bind(&Button::handleStateUpdateMessage,
                  this,
                  std::placeholders::_1));
  }

  void Button::loop()
  {
    voltage_t value = digitalRead(Configuration::getButtonPin());
    switch (value)
    {
    case Configuration::getButtonVoltageNotPressed():
      pressed = false;
      break;
    case Configuration::getButtonVoltagePressed():
      if (!pressed)
      {
        toggleState();
        pressed = true;
      }
      break;
    }
  }

  void Button::toggleState()
  {
    switch (currentState)
    {
    case Button::State::OFF:
    case Button::State::TURNING_OFF:
      mqttClient.publish(Configuration::getMqttTopicButtonSetState(), Configuration::getMqttPayloadOn());
      currentState = Button::State::TURNING_ON;
      break;
    case Button::State::ON:
    case Button::State::TURNING_ON:
    default:
      mqttClient.publish(Configuration::getMqttTopicButtonSetState(), Configuration::getMqttPayloadOff());
      currentState = Button::State::TURNING_OFF;
      break;
    }
  }

  void Button::handleStateUpdateMessage(const std::string &message)
  {
    if (message == Configuration::getMqttPayloadOff())
    {
      currentState = Button::State::OFF;
    }
    else if (message == Configuration::getMqttPayloadOn())
    {
      currentState = Button::State::ON;
    }
  }

  Button::State Button::getState() const
  {
    return currentState;
  }

  bool Button::isBeingPressed() const
  {
    return pressed;
  }

} // namespace LightSwitch
