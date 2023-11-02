#ifndef FUNGSI_H
#define FUNGSI_H

#include "config.h"

void readTemp(float &temp)
{
    temperature.requestTemperatures();
    temp = temperature.getTempCByIndex(0);
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
    // PH = (avgPH * m) + bPH; //Nilai PH asli
    PH = (avgPH * m) + bPH + 2; //Nilai PH rekayasa
    // Serial.println(PH);
}

void bacasensorlevel(int &atas, int &bawah)
{
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distance = duration * 0.034 / 2;

    // Prints the distance in the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distance);

    if (distance > 8)
    {
        atas = HIGH;
    }
    else
    {
        atas = LOW;
    }
    if (distance < 17)
    {
        bawah = HIGH;
    }
    else
    {
        bawah = LOW;
    }
    Serial.print("atas : ");
    Serial.println(atas);
    Serial.print("bawah : ");
    Serial.println(bawah);

    delay(1000);
}

void pompapenguras()
{
    int kondisiatas, kondisibawah;
    bacasensorlevel(kondisiatas, kondisibawah);
    while (kondisibawah == HIGH)
    {
        digitalWrite(pinRelayPenguras, LOW);
        bacasensorlevel(kondisiatas, kondisibawah);
    }
    digitalWrite(pinRelayPenguras, HIGH);
    
}
void pompaPengisi(){
    int kondisiatas, kondisibawah;
    bacasensorlevel(kondisiatas, kondisibawah);
    while (kondisiatas == HIGH)
    {
        digitalWrite(pinRelayPengisi, LOW);
        bacasensorlevel(kondisiatas, kondisibawah);
    }
    digitalWrite(pinRelayPengisi, HIGH);
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
}

void sentDataThingSpeek(float temp, float ph)
{
    // kirim data ke thingspeak
    ThingSpeak.setField(1, temp);
    ThingSpeak.setField(2, ph);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (x == 200)
    {
        Serial.println("Channel update successful.");
    }
    else
    {
        Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
}
#endif // FUNGSI_H