#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include "OTAUpdateHandler.h"

const long DEFAULT_INTERVAL = 1 * 60 * 60 * 1000; // 1 hour

OTAUpdateHandler::OTAUpdateHandler(String updateServerIP, String version) {
  _updateServerIP = updateServerIP;
  _version = version;

  _updateInterval = DEFAULT_INTERVAL;
  _lastUpdateCheck = 0;
}

void OTAUpdateHandler::setup() {
}

void OTAUpdateHandler::loop() {
  checkForUpdate();
}

void OTAUpdateHandler::startUpdate() {
  ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
  ESPhttpUpdate.update(buildEnpointUrl(), _version);
}

void OTAUpdateHandler::checkForUpdate() {
  unsigned long now = millis();
  if (
    WiFi.status() == WL_CONNECTED
    && now >= _lastUpdateCheck + _updateInterval
  ) {
    startUpdate();
    _lastUpdateCheck = now;
  }
}

void OTAUpdateHandler::setInterval(long interval) {
  _updateInterval = interval;
}

String OTAUpdateHandler::buildEnpointUrl() {
  return String("http://") + _updateServerIP + String("/ota");
}