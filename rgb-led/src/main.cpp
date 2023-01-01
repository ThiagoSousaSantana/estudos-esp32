#include <Arduino.h>

const byte ledPins[] = {15, 2, 4}; // define red, green, blue led pins
const byte chns[] = {0, 1, 2};     // define the pwm channels
int red, green, blue;

void setColor(byte r, byte g, byte b)
{
  delay(10);
  ledcWrite(chns[0], 255 - r); // Common anode LED, low level to turn on the led.
  ledcWrite(chns[1], 255 - g);
  ledcWrite(chns[2], 255 - b);
}

void setup()
{
  for (int i = 0; i < 3; i++)
  {
    // setup the pwm channels,1KHz,8bit
    ledcSetup(chns[i], 1000, 8);
    ledcAttachPin(ledPins[i], chns[i]);
  }
}

void loop()
{
  int red = 168;
  int green = 50;
  int blue = 50;
  
  for (green; green <= 168; green++)
  {
    setColor(red, green, blue);
  }

  for (red; red >= 50; red--)
  {
    setColor(red, green, blue);
  }

  for (blue; blue <= 168; blue++)
  {
    setColor(red, green, blue);
  }

  for (green; green >= 50; green--)
  {
    setColor(red, green, blue);
  }

  for (red; red <= 168; red++)
  {
    setColor(red, green, blue);
  }

  for (blue; blue >= 50; blue--)
  {
    setColor(red, green, blue);
  }
  
}