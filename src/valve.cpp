#include "../include/logging.h"
#include "../include/valve.h"
#include "esp_timer.h"

#define RELAY_STATE_ON 1
#define RELAY_STATE_OFF 0

Valve::Valve(uint8_t pin) {
  this->pin = pin;
  this->timer = NULL;
  this->state = RELAY_STATE_OFF;
  pinMode(pin, OUTPUT);
}
void set(uint8_t pin, void* _value) {
  uint8_t* value = (uint8_t*)_value;
  digitalWrite(pin, *value);
  LOG("Vavle %d has been to %d",pin, value);
}

void Valve::open(int seconds) {
  LOG("Setting valve %d to open for %d seconds", this->pin, seconds);
  this->state = RELAY_STATE_ON;
  set(this->pin, &this->state);

  esp_timer_create_args_t timer_args;
  timer_args.callback = (esp_timer_cb_t)set;
  this->state = RELAY_STATE_OFF;
  timer_args.arg = &this->state;

  esp_timer_create(&timer_args, &this->timer);
  esp_timer_start_once(timer, seconds * 1000000);
}

void Valve::close() {
  this->state = RELAY_STATE_OFF;
  set(this->pin, &this->state);
  if(esp_timer_is_active(this->timer)) {
    esp_timer_stop(this->timer);
  } else {
    LOG("Timer is not active");
  }
}