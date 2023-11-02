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
#include "ThingSpeak.h"

// WIFI
const char *ssid = "Ahmad Zulfadli";
const char *password = "sampoerna12";

// NTP
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 25200;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// THINGSPEAK
WiFiClient client;
unsigned long myChannelNumber = 2300657;
const char *myWriteAPIKey = "07Z4VPZ7XHOKT98B";

// FUZZY
Fuzzy *fuzzy = new Fuzzy();

// DS18B20
#define ONE_WIRE_BUS 5 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temperature(&oneWire);

// LCD
LiquidCrystal_I2C lcd(0x3F, 20, 4);

// PH
#define ph_pin 34
unsigned long int avgValue;
float avgPH;
float b;
int buf[10],temp;

float m = (5.2 - 4.3) / (123.80 - 117.90); // Kemiringan
float bPH = 5.2 - (m * 123.80); // Bias

// LEVEL WITH ULTRASONIC
const int trigPin = 12;
const int echoPin = 13;

//define sound speed in cm/uS
long duration;
float distance;

// OUTPUT
int pinRelayPenguras = 14;
int pinRelayPengisi = 27;
int pinRelayCooler = 26;
int pinRelayHeater = 25;

// MILLIS
unsigned long previousMillis = 0;
const long interval = 10000;

#endif // CONFIG_H