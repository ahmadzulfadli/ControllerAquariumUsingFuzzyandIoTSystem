#ifndef FUNGSI_CONTROLLER_AQUARIUM_H
#define FUNGSI_CONTROLLER_AQUARIUM_H
#include "config.h"

void baca_suhu(float suhu)
{
    DS18B20.requestTemperatures();
    suhu = DS18B20.getTempCByIndex(0);
}

void baca_pH(float Po)
{
    nilai_analog_PH = analogRead(ph_pin);
    TeganganPh = 5 / 1023.0 * nilai_analog_PH;
    PH_step = (PH4 - PH7) / 3;
    Po = 7.00 + ((PH7 - TeganganPh) / PH_step);
}

int bacasensorlevel(int atas, int bawah)
{
    nilai_atas = analogRead(A1);
    nilai_bawah = analogRead(A0);
    if (nilai_atas > 4)
    {
        atas = HIGH;
    }
    else
    {
        atas = LOW;
    }
    if (nilai_bawah > 4)
    {
        bawah = HIGH;
    }
    else
    {
        bawah = LOW;
    }
}

int pompaawal()
{
    int kondisiatas, kondisibawah;
    bacasensorlevel(kondisiatas, kondisibawah);
    while (kondisiatas == LOW)
    {
        digitalWrite(pinpengisi, HIGH);
    }
    digitalWrite(pinpengisi, LOW);
}

int pompapenguras()
{
    int kondisiatas, kondisibawah;
    bacasensorlevel(kondisiatas, kondisibawah);
    while (kondisibawah == HIGH)
    {
        digitalWrite(pinpenguras, HIGH);
    }
    digitalWrite(pinpenguras, LOW);
    while (kondisiatas == LOW)
    {
        digitalWrite(pinpengisi, HIGH);
    }
    digitalWrite(pinpengisi, LOW);
}

void sendDataToWebserver(){
    
}

int display()
{
    DateTime now = rtc.now();
    baca_suhu(nilai_suhu);
    baca_pH(nilai_pH);

    lcd.setCursor(0, 0);
    lcd.print(now.day(), DEC);
    Serial.print(now.day(), DEC);
    lcd.print("-");
    Serial.print("-");
    lcd.print(now.month(), DEC);
    Serial.print(now.month(), DEC);
    lcd.print("-");
    Serial.print("-");
    lcd.print(now.year(), DEC);
    Serial.print(now.year(), DEC);
    lcd.print(" ");
    Serial.print(" ");
    lcd.print(now.hour(), DEC);
    Serial.print(now.hour(), DEC);
    lcd.print(":");
    Serial.print(":");
    lcd.print(now.minute(), DEC);
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.print(now.second(), DEC);

    lcd.setCursor(0, 1);
    Serial.print(", ");
    lcd.print("S:");
    Serial.print("Suhu Air: ");
    lcd.print(nilai_suhu);
    Serial.print(nilai_suhu);
    lcd.write(0xDF);
    lcd.print("C");
    Serial.print(" *C");
    Serial.print(", ");
    lcd.print(" p:");
    Serial.print("pH Air: ");
    lcd.print(nilai_pH, 2);
    Serial.print(nilai_pH, 2);
    Serial.println();
}

#endif // FUNGSI_CONTROLLER_AQUARIUM_H