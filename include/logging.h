#pragma once
#define MAX_LOG_SIZE 256
#define LOG(x, ...)                 \
  do {                              \
    char buf[MAX_LOG_SIZE];         \
    sprintf(buf, x, ##__VA_ARGS__); \
    Serial.println(buf);            \
  } while (0)