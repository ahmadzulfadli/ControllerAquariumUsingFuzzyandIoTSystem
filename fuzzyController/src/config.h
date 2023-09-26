#ifndef CONFIG_CONTROLLER_AQUARIUM_H
#define CONFIG_CONTROLLER_AQUARIUM_H
#include <Arduino.h>
#include <Fuzzy.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


// FUZZY
Fuzzy *fuzzy = new Fuzzy();

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DS18B20
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

// pH
int ph_pin = 34;
float nilai_analog_PH;
float TeganganPh;
float PH_step;
float PH4 = 4.0;
float PH7 = 7.0;
float Po;

// Level
#define pinAtas 35
#define pinBawah 36
int nilai_atas;
int nilai_bawah;
int pinRelayPengisi = 32;
int pinRelayPenguras = 33;

// UPDATE TIME
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 25200;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds );

// OUTPUT
int pinRelayHeater = 25;
int pinRelayCooler = 26;

// millis
unsigned long previousMillis = 0;
const long interval = 3000;

#endif // CONFIG_CONTROLLER_AQUARIUM_H