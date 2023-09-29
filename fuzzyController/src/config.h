#ifndef CONFIG_CONTROLLER_AQUARIUM_H
#define CONFIG_CONTROLLER_AQUARIUM_H
#include <Arduino.h>
#include <Fuzzy.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
// #include <WiFiUdp.h>
// #include <NTPClient.h>


// WIFI
const char *ssid = "OwlCities";
const char *password = "cirikkaulah";

// FUZZY
Fuzzy *fuzzy = new Fuzzy();

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DS18B20
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

// pH
int ph_pin = 34;
float nilai_analog_PH;
float TeganganPh;
float PH_step;
float PH4 = 4.0;
float PH7 = 7.0;

// Level
#define pinAtas 35
#define pinBawah 32
int nilai_atas;
int nilai_bawah;
int pinRelayPengisi = 14;
int pinRelayPenguras = 12;

// UPDATE TIME
// WiFiUDP ntpUDP;
// const long utcOffsetInSeconds = 25200;
// NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds );

// OUTPUT
int pinRelayHeater = 19;
int pinRelayCooler = 18;

// WEB SERVER
const char *host = "192.168.80.240";
const int port = 80;

// millis
unsigned long previousMillis = 0;
const long interval = 3000;

#endif // CONFIG_CONTROLLER_AQUARIUM_H