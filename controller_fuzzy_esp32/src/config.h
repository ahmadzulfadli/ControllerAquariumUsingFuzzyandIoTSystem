#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Fuzzy.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// WIFI
const char* ssid = "Ahmad Zulfadli";
const char* password = "sampoerna12";

// NTP
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 25200;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// FUZZY
Fuzzy *fuzzy = new Fuzzy();

//DS18B20
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LCD
LiquidCrystal_I2C lcd(0x27,20,4);

// PH
#define ph_pin 34
float nilai_analog_PH;
float TeganganPh;
float PH_step;
float PH4 = 4.0;
float PH7 = 7.0;

// LEVEL
#define pinAtas 35
#define pinBawah 32
#define pinRelayPengisi 14
#define pinRelayPenguras 12
int nilai_atas;
int nilai_bawah;


// OUTPUT
#define pinRelayHeater 19
#define pinRelayCooler 18

// WEB SERVER
const char *host = "192.168.80.240";
const int port = 80;

// MILLIS
unsigned long previousMillis = 0;
const long interval = 10000;

#endif // CONFIG_H