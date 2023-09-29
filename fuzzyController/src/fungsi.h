// #ifndef FUNGSI_CONTROLLER_AQUARIUM_H
// #define FUNGSI_CONTROLLER_AQUARIUM_H
// #include "config.h"

// void baca_suhu(float suhu)
// {
//     DS18B20.requestTemperatures();
//     suhu = DS18B20.getTempCByIndex(0);
// }

// void baca_pH(float Po)
// {
//     nilai_analog_PH = analogRead(ph_pin);
//     TeganganPh = 5 / 1023.0 * nilai_analog_PH;
//     PH_step = (PH4 - PH7) / 3;
//     Po = 7.00 + ((PH7 - TeganganPh) / PH_step);
// }

// int bacasensorlevel(int atas, int bawah)
// {
//     nilai_atas = analogRead(pinAtas);
//     nilai_bawah = analogRead(pinBawah);
//     if (nilai_atas > 4)
//     {
//         atas = HIGH;
//     }
//     else
//     {
//         atas = LOW;
//     }
//     if (nilai_bawah > 4)
//     {
//         bawah = HIGH;
//     }
//     else
//     {
//         bawah = LOW;
//     }
// }

// int pompaawal()
// {
//     int kondisiatas, kondisibawah;
//     bacasensorlevel(kondisiatas, kondisibawah);
//     while (kondisiatas == LOW)
//     {
//         digitalWrite(pinRelayPengisi, HIGH);
//     }
//     digitalWrite(pinRelayPengisi, LOW);
// }

// int pompapenguras()
// {
//     int kondisiatas, kondisibawah;
//     bacasensorlevel(kondisiatas, kondisibawah);
//     while (kondisibawah == HIGH)
//     {
//         digitalWrite(pinRelayPenguras, HIGH);
//     }
//     digitalWrite(pinRelayPenguras, LOW);
//     while (kondisiatas == LOW)
//     {
//         digitalWrite(pinRelayPengisi, HIGH);
//     }
//     digitalWrite(pinRelayPengisi, LOW);
// }

// // void sendDataToWebserver(float data1, float data2){
// //     //--------------------------------------------
// //     // Send data to server
// //     WiFiClient client;
// //     if (!client.connect(host, port))
// //     {
// //         Serial.println("Connection failed");
// //         // lcd.clear();
// //         // lcd.setCursor(0, 0);
// //         // lcd.print("Connection failed");
// //         delay(1000);
// //         return;
// //     }

// //     // pengiriman nilai sensor ke web server
// //     // windows
// //     String apiUrl = "http://localhost:8000/add/data?";
// //     // linux
// //     // String apiUrl = "http://localhost:8000/add/data?";

// //     apiUrl += "mode=save";
// //     apiUrl += "&temp=" + String(data1);
// //     apiUrl += "&ph_meter=" + String(data2);

// //     // Set header Request
// //     client.print(String("GET ") + apiUrl + " HTTP/1.1\r\n" +
// //                  "Host: " + host + "\r\n" +
// //                  "Connection: close\r\n\r\n");

// //     // Pastikan tidak berlarut-larut
// //     unsigned long timeout = millis();
// //     while (client.available() == 0)
// //     {
// //         if (millis() - timeout > 3000)
// //         {
// //             Serial.println(">>> Client Timeout !");
// //             Serial.println(">>> Operation failed !");
// //             client.stop();
// //             return;
// //         }
// //     }

// //     // Baca hasil balasan dari PHP
// //     while (client.available())
// //     {
// //         String line = client.readStringUntil('\r');
// //         Serial.println(line);
// //     }

// //     //--------------------------------------------
// // }

// // int display(float data1, float data2)
// // {
// //     timeClient.update();

// //     // Display time to LCD
// //     lcd.setCursor(0, 0);
// //     lcd.print(timeClient.getFormattedTime());

// //     // Display suhu to LCD
// //     lcd.setCursor(0, 1);
// //     lcd.print("Suhu: ");
// //     lcd.print(data1);
// //     lcd.print(" C");

// //     // Display pH to LCD
// //     lcd.setCursor(9, 1);
// //     lcd.print("pH: ");
// //     lcd.print(data2);

// //     // Display ALl to Serial
// //     Serial.print(timeClient.getFormattedTime());
// //     Serial.print(" | Suhu: ");
// //     Serial.print(data1);
// //     Serial.print(" C | pH: ");
// //     Serial.println(data2);
// // }

// #endif // FUNGSI_CONTROLLER_AQUARIUM_H