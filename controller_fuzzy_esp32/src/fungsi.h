#ifndef FUNGSI_H
#define FUNGSI_H

#include "config.h"

void readTemp(float &temp)
{
    temperature.requestTemperatures();
    temp = temperature.getTempCByIndex(0);
    // temp = random(0, 50);
}

void readPH(float &PH)
{
    for (int i = 0; i < 20; i++)
    {
        for (int i = 0; i < 10; i++) // Get 10 sample value from the sensor for smooth the value
        {
            buf[i] = analogRead(ph_pin);
            delay(10);
        }
        for (int i = 0; i < 9; i++) // sort the analog from small to large
        {
            for (int j = i + 1; j < 10; j++)
            {
                if (buf[i] > buf[j])
                {
                    temp = buf[i];
                    buf[i] = buf[j];
                    buf[j] = temp;
                }
            }
        }
        avgValue = 0;
        for (int i = 2; i < 8; i++) // take the average value of 6 center sample
            avgValue += buf[i];
        float phValue = (float)avgValue * 3.3 / 4095 / 6; // convert the analog into millivolt
        phValue = 4.0 * phValue;                          // convert the millivolt into pH value
        avgPH += phValue;
        delay(500);
    }
    Serial.println(avgPH);
    PH = (avgPH*m) + bPH;
    Serial.println(PH);
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

void display(float temp, float PH)
{
    timeClient.update();

    Serial.println(timeClient.getFormattedTime());
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("PH: ");
    Serial.println(PH);

    lcd.setCursor(0, 0);
    lcd.print(timeClient.getFormattedTime());

    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(temp, 1);
    lcd.print("C ");
    lcd.print("PH:");
    lcd.print(PH, 1);
    lcd.print(" pH");
}

#endif // FUNGSI_H