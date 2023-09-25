#ifndef CONFIG_CONTROLLER_AQUARIUM_H
#define CONFIG_CONTROLLER_AQUARIUM_H
#include <Arduino.h>
#include <Fuzzy.h>
// FUZZY
Fuzzy *fuzzy = new Fuzzy();

// millis
unsigned long previousMillis = 0;
const long interval = 3000;

#endif // CONFIG_CONTROLLER_AQUARIUM_H