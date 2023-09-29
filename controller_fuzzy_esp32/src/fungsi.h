#ifndef FUNGSI_H
#define FUNGSI_H

#include "config.h"

void readTemp(float &temp){
    sensors.requestTemperatures();
    // temp = sensors.requestTemperatures();
    temp = random(0, 50);
}

void readPH(float &PH)
{
    nilai_analog_PH = analogRead(ph_pin);
    TeganganPh = 5 / 1023.0 * nilai_analog_PH;
    PH_step = (PH4 - PH7) / 3;
    // PH = 7.00 + ((PH7 - TeganganPh) / PH_step);
    PH = random(0, 15);
}

void bacasensorlevel(int atas, int bawah)
{
    nilai_atas = analogRead(pinAtas);
    nilai_bawah = analogRead(pinBawah);
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

void pompaawal()
{
    int kondisiatas, kondisibawah;
    bacasensorlevel(kondisiatas, kondisibawah);
    while (kondisiatas == LOW)
    {
        digitalWrite(pinRelayPengisi, HIGH);
    }
    digitalWrite(pinRelayPengisi, LOW);
}

void pompapenguras()
{
    int kondisiatas, kondisibawah;
    bacasensorlevel(kondisiatas, kondisibawah);
    while (kondisibawah == HIGH)
    {
        digitalWrite(pinRelayPenguras, HIGH);
    }
    digitalWrite(pinRelayPenguras, LOW);
    while (kondisiatas == LOW)
    {
        digitalWrite(pinRelayPengisi, HIGH);
    }
    digitalWrite(pinRelayPengisi, LOW);
}

void display(float temp, float PH){
    timeClient.update();

    Serial.println(timeClient.getFormattedTime());
    Serial.println(temp);
    Serial.println(PH);
}

#endif // FUNGSI_H