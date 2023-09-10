#include <WiFi.h>
#include <esp_timer.h>
#include <unistd.h>

#define RELAY_PIN 4
#define RELAY_STATE_ON 1
#define RELAY_STATE_OFF 0
#define TIME_BASED 0
#define SENSOR_BASED 1
#define MAX_LOG_SIZE 255

#define LOG(x, ...)                 \
  do {                              \
    char buf[MAX_LOG_SIZE];         \
    sprintf(buf, x, ##__VA_ARGS__); \
    Serial.println(buf);            \
  } while (0)

const char* ssid = "Lochness";
const char* passwd = "secretmonster2021";
WiFiClient client;
uint8_t mode = TIME_BASED;

void connect() {
  WiFi.begin(ssid, passwd);
  LOG("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {}
  LOG("Connected");
}

void set_relay(uint8_t* v) {
  uint8_t value = *v;
  digitalWrite(RELAY_PIN, value);
  LOG("relay value has been to %d", value);
}

void openValve(int seconds) {
  uint8_t relay_state = RELAY_STATE_ON;
  set_relay(&relay_state);
  
  esp_timer_handle_t close_timer;
  esp_timer_create_args_t timer_args;
  timer_args.callback = (esp_timer_cb_t)set_relay;
  relay_state = RELAY_STATE_OFF;
  timer_args.arg = &relay_state;
  esp_timer_create(&timer_args, &close_timer);
  esp_timer_start_once(close_timer, seconds * 1000000);
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  connect();
}

void loop() {

}