#include "config.h"
#include "fungsi.h"
#include "setupFuzzy.h"

void setup()
{
  Serial.begin(115200);

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

  // ULTRASONIC
  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connected to ...");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(2000);
  lcd.clear();

  // DS18B20
  temperature.begin();

  // FUZZY
  setupFuzzy();

  // RELAY
  pinMode(pinRelayHeater, OUTPUT);
  pinMode(pinRelayCooler, OUTPUT);
  pinMode(pinRelayPengisi, OUTPUT);
  pinMode(pinRelayPenguras, OUTPUT);

  digitalWrite(pinRelayHeater, HIGH);
  digitalWrite(pinRelayCooler, HIGH);
  digitalWrite(pinRelayPengisi, HIGH);
  digitalWrite(pinRelayPenguras, HIGH);

  // POMPA AWAL
  pompaPengisi();

  // THINGSPEAK
  ThingSpeak.begin(client);
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

    // menampilkan data di lcd
    display(temp, PH);

    fuzzy->setInput(1, temp);
    fuzzy->setInput(2, PH);
    fuzzy->fuzzify();

    float heater = fuzzy->defuzzify(1);
    float cooler = fuzzy->defuzzify(2);
    float pump = fuzzy->defuzzify(3);

    Serial.println("====================================");
    Serial.println(heater);
    Serial.println(cooler);
    if (pump > 0)
    {
      Serial.print("Pump: ");
      Serial.println("ON");

      pompapenguras();
      pompaPengisi();
    }
    
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
    
    Serial.println("====================================");

    // mengirim data ke thingspeak
    sentDataThingSpeek(temp, PH);
  }
}
