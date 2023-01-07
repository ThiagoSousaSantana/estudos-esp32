#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT 8  // The number of led
#define LEDS_PIN 2    // define the pin connected to the Freenove 8 led strip
#define CHANNEL 0     // RMT channel
#define BUTTON_PIN 13 // define the pin connected to the button
#define BUZZER_PIN 12 // define the pin connected to the buzzer

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

// Collors
const int green[3] = {0, 255, 0};
const int red[3] = {255, 0, 0};
const int blue[3] = {0, 0, 255};

// Time variables
long delayMillis = 200;
long previousMillis = 0; 

const int ledPins[8] = {0, 1, 2, 3, 4, 5, 6, 7};
int ledStatus[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int ledCount = 0;

void setup()
{
  strip.begin();
  strip.setBrightness(20);
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis < delayMillis){
    if (digitalRead(BUTTON_PIN) == LOW) {
      if (ledStatus[0] == HIGH)
      {
        strip.setAllLedsColor(green[0], green[1], green[2]);
        ledCount = 0;
        ledStatus[0] = LOW;
        
        delay(2000);
        
        strip.setAllLedsColor(0, 0, 0);
      } else {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(50);
        digitalWrite(BUZZER_PIN, LOW);
      }
    }
  }
  else
  {
    if (ledCount > 0 && ledStatus[ledCount - 1] == HIGH) 
    {
      Serial.println("Apagando led: " + ledCount -1);
      strip.setLedColorData(ledPins[ledCount - 1], 0, 0, 0);  
      ledStatus[ledCount - 1] = LOW;

      if(ledCount >= 8) {
        ledCount = 0;
      }
    }
    
    if (ledStatus[ledCount] == LOW) 
    {
      Serial.println("Acendendo led: " + ledCount);
      strip.setLedColorData(ledPins[ledCount], blue[0], blue[1], blue[2]);
      ledStatus[ledCount] = HIGH;
      ledCount++;
      previousMillis = currentMillis;
    }
    strip.show();
  }
  
}