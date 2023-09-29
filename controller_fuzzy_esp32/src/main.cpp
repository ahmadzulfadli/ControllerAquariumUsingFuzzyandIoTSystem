#include "config.h"
#include "fungsi.h"
#include "setupFuzzy.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello World!");

  // WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // DS18B20
  sensors.begin();

  // LCD
  lcd.init();
  lcd.backlight();

  // FUZZY
  setupFuzzy();

  //POMPA AWAL
  pompaawal();
}

void loop()
{
  // MILLIS
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    float temp, PH;
    readTemp(temp);
    readPH(PH);

    fuzzy->setInput(1, temp);
    fuzzy->setInput(2, PH);
    fuzzy->fuzzify();

    float heater = fuzzy->defuzzify(1);
    float cooler = fuzzy->defuzzify(2);
    float pump = fuzzy->defuzzify(3);

    Serial.println("====================================");
    if (heater > 0)
    {
      Serial.print("Heater: ");
      Serial.println("ON");

      digitalWrite(pinRelayHeater, HIGH);
    }
    if (cooler > 0)
    {
      Serial.print("Cooler: ");
      Serial.println("ON");

      digitalWrite(pinRelayCooler, HIGH);
    }
    if (pump > 0)
    {
      Serial.print("Pump: ");
      Serial.println("ON");

      pompapenguras();
    }
    Serial.println("====================================");

    display(temp, PH);
  }
}
