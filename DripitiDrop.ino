#include <WiFi.h>
#include <esp_timer.h>
#include <unistd.h>
#include "esp32-hal-gpio.h"
#include "esp32-hal.h"
#include "include/valve.h"
#include "include/logging.h"
#include <AsyncUDP.h>

#define RELAY_STATE_ON 1
#define RELAY_STATE_OFF 0

#define MAX_LOG_SIZE 255

const char* ssid = "Lochness";
const char* passwd = "secretmonster2021";

WiFiClient client;
Valve valve(8);
AsyncUDP udp;

void handleUDP(AsyncUDPPacket packet);

void connect() {
  WiFi.begin(ssid, passwd);
  LOG("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {}
  LOG("Connected");
  udp.listen(1234);
  udp.onPacket([](AsyncUDPPacket packet) {
    handleUDP(packet);
  });
}

void setup() {
  Serial.begin(9600);
  connect();
  LOG("Setting up valve");
  valve.open(5);
}


void handleUDP(AsyncUDPPacket packet) {
  LOG("Received packet from %s:%d", packet.remoteIP().toString().c_str(), packet.remotePort());
  LOG("Data: %s", packet.data());
  packet.printf("Got %u bytes of data", packet.length());
}
void loop() {
}