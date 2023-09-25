#include "config.h"
#include "fuzzyConfig.h"

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupFuzzy();
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Millis
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    float temperature = random(16, 34);
    float pH = random(0, 15);

    fuzzy->setInput(1, temperature);
    fuzzy->setInput(2, pH);

    fuzzy->fuzzify();

    float heater = fuzzy->defuzzify(1);
    float cooler = fuzzy->defuzzify(2);
    float pump = fuzzy->defuzzify(3);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" pH: ");
    Serial.println(pH);
    Serial.println("====================================");

    if (heater > 0)
    {
      Serial.print("Heater: ");
      Serial.println("ON");
    }
    if (cooler > 0)
    {
      Serial.print("Cooler: ");
      Serial.println("ON");
    }
    if (pump > 0)
    {
      Serial.print("Pump: ");
      Serial.println("ON");
    }
    Serial.println("====================================");
  }
}
