#include "config.h"
#include "fuzzyConfig.h"
#include "fungsi.h"

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupFuzzy();

  // water check
  pompaawal();
}

void loop()
{
  // Millis
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    float temperature, pH;
    baca_suhu(temperature);
    baca_pH(pH);

    fuzzy->setInput(1, temperature);
    fuzzy->setInput(2, pH);

    fuzzy->fuzzify();

    float heater = fuzzy->defuzzify(1);
    float cooler = fuzzy->defuzzify(2);
    float pump = fuzzy->defuzzify(3);

    display();

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
  }
}
