#include "config.h"
#include "fungsi.h"
#include "setupFuzzy.h"

void setup()
{
  Serial.begin(115200);

  // RELAY
  pinMode(pinRelayHeater, OUTPUT);
  pinMode(pinRelayCooler, OUTPUT);
  pinMode(pinRelayPengisi, OUTPUT);
  pinMode(pinRelayPenguras, OUTPUT);

  digitalWrite(pinRelayHeater, HIGH);
  digitalWrite(pinRelayCooler, HIGH);
  digitalWrite(pinRelayPengisi, HIGH);
  digitalWrite(pinRelayPenguras, HIGH);

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

    // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connected to ...");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  // delay(2000);
  // lcd.clear();

  // DS18B20
  temperature.begin();

  // FUZZY
  setupFuzzy();

  // POMPA AWAL
  //  pompaawal();
}

void loop()
{
  // MILLIS
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    avgPH = 0;

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
    Serial.println(heater);
    Serial.println(cooler);
    if (heater > 0)
    {
      Serial.print("Heater: ");
      Serial.println("ON");

      digitalWrite(pinRelayHeater, LOW);
    }
    if (cooler > 0)
    {
      Serial.print("Cooler: ");
      Serial.println("ON");

      digitalWrite(pinRelayCooler, LOW);
    }
    if (pump > 0)
    {
      Serial.print("Pump: ");
      Serial.println("ON");

      // pompapenguras();
    }
    Serial.println("====================================");

    display(temp, PH);
  }
}
