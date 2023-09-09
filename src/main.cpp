#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define power_pin D5
#define statusLED D2

void blinkLed(int blinkQuantity, int blinkSpacing)
{
  int counter = 0;
  while (counter < blinkQuantity)
  {
    counter++;
    // digitalWrite(statusLED, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(blinkSpacing);
    // digitalWrite(statusLED, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    delay(blinkSpacing);
  }
}

bool isHome()
{
  int numberOfTries = 0;

  WiFi.disconnect();
  delay(2000);
  WiFi.begin("SSID", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED && numberOfTries < 150)
  {
    delay(100);
    Serial.print(".");
    numberOfTries++;
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void setup()
{
  pinMode(power_pin, OUTPUT);
  digitalWrite(power_pin, LOW);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  delay(100);

  delay(300000);
}

void loop()
{
  if (isHome())
  {
    Serial.println("Home");
    blinkLed(5, 200);
    analogWrite(power_pin, 128);
    delay(100);
    ESP.restart();
  }
  delay(60000);
}