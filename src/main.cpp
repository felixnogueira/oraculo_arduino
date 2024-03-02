#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Thread.h>
#include <ThreadController.h>

// some parts of this code were not used, as it was written in a learning process. it will be changed later to be under better practices.
// TODO: review and rewrite.

Thread firstT = Thread();
Thread secondT = Thread();

// definers
#define NUM_LEDS 82
#define BUTTON_COUNT 6
#define DATA_PIN 3

// library settings
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

// button variables
const int s1 = 2;
const int s2 = 4;
const int s3 = 5;
const int s4 = 6;
const int s5 = 7;
const int s6 = 8;

uint32_t b1P;
uint32_t b2P;
uint32_t b3P;
uint32_t b4P;
uint32_t b5P;
uint32_t b6P;
uint32_t closeApp;

// led strip variables - brightness
int fullBrightness = 255;
int mediumBrightness = 170;
int lowBrightness = 100;
int noBrightness = 0;

// led strip variables - colors
uint32_t redC = strip.Color(255, 0, 0);
uint32_t greenC = strip.Color(0, 255, 0);
uint32_t blueC = strip.Color(0, 0, 255);
uint32_t blackC = strip.Color(0, 0, 0);
uint32_t whiteC = strip.Color(255, 255, 255);

// delay variables
const int delayOn = 50;
const int delayOff = 10;
const int btnEffectOn = 50;
const int btnEffectOff = 50;
const int delayE = 30000;
const int requiredDuration = 20; // Required active duration in milliseconds

// Array to store the button press start times
unsigned long buttonPressStartTimes[BUTTON_COUNT] = {0};

bool shouldClose = false; // Initialize to false

unsigned long startTime = 0;
unsigned long duration = 3000; // 3 seconds in milliseconds

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// setup config
void setup()
{
  // serial setup
  Serial.begin(9600);
  Serial.println("Start");

  // pinmode setup
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < 6; i++)
  {
    pinMode(s1, INPUT_PULLUP);
    pinMode(s2, INPUT_PULLUP);
    pinMode(s3, INPUT_PULLUP);
    pinMode(s4, INPUT_PULLUP);
    pinMode(s5, INPUT_PULLUP);
    pinMode(s6, INPUT_PULLUP);
  }

  // initialization setup
  strip.begin();
  strip.setBrightness(255);
  strip.clear();
  for (int i = 0; i < 64; i++)
  {
    strip.setPixelColor(i, redC);
  }
  strip.show();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// function to light up every led
void lightup()
{
  for (int i = 0; i < 64; i++)
  {
    strip.setPixelColor(i, redC);
  }
  strip.show();
}

void lightoffBtns()
{
  for (int i = 64; i < 82; i++)
  {
    strip.setPixelColor(i, blackC);
  }
  strip.show();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Checksum function

void btn1Active()
{

  Serial.println("btnAct");
  // turn off button lights
  lightoffBtns();
  // turn on strip lights for every led except the button leds
  lightup();
  // turn on and off 5 times the button leds
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 64 + i;
      strip.setPixelColor(ledIndex, redC); // Red
      strip.show();
      delay(btnEffectOn);
    }
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 64 + i;
      strip.setPixelColor(ledIndex, blackC); // Red
      strip.show();
      delay(btnEffectOff);
    }
    delay(btnEffectOff);

    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 64 + i;
      strip.setPixelColor(ledIndex, redC);
      strip.show();
      delay(btnEffectOn);
    }
  }

  for (int i = 10; i < 63; i++)
  {
    strip.setPixelColor(i, blackC);
    strip.show();
    delay(delayOff);
  }

  Serial.println("button1P");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void btn2Active()
{
  Serial.println("btnAct");
  // turn off button lights
  lightoffBtns();
  // turn on strip lights for every led except the button leds
  lightup();
  // turn on and off 5 times the button leds
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 67 + i;
      strip.setPixelColor(ledIndex, redC); // Red
      strip.show();
      delay(btnEffectOn);
    }
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 67 + i;
      strip.setPixelColor(ledIndex, blackC); // Red
      strip.show();
      delay(btnEffectOff);
    }
    delay(btnEffectOff);

    for (int k = 0; k < 3; k++)
    {
      int ledIndex = 67 + k;
      strip.setPixelColor(ledIndex, redC);
      strip.show();
      delay(btnEffectOn);
    }
  }

  // turn off the strip leds that create the effect

  for (int i = 19; i < 64; i++)
  {
    strip.setPixelColor(i, blackC);

    strip.show();
    delay(delayOff);
  }

  for (int i = 0; i < 12; i++)
  {
    strip.setPixelColor(i, blackC);

    strip.show();
    delay(delayOff);
  }

  Serial.println("button2P");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void btn3Active()
{
  Serial.println("btnAct");
  // turn off button lights
  lightoffBtns();
  // turn on strip lights for every led except the button leds
  lightup();
  // turn on and off 5 times the button leds
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 70 + i;
      strip.setPixelColor(ledIndex, redC); // Red
      strip.show();
      delay(btnEffectOn);
    }
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 70 + i;
      strip.setPixelColor(ledIndex, blackC); // Red
      strip.show();
      delay(btnEffectOff);
    }
    delay(btnEffectOff);

    for (int k = 0; k < 3; k++)
    {
      int ledIndex = 70 + k;
      strip.setPixelColor(ledIndex, redC);
      strip.show();
      delay(btnEffectOn);
    }
  }

  // turn off the strip leds that create the effect

  for (int i = 30; i < 64; i++)
  {
    strip.setPixelColor(i, blackC);

    strip.show();
    delay(delayOff);
  }

  for (int i = 0; i < 22; i++)
  {
    strip.setPixelColor(i, blackC);

    strip.show();
    delay(delayOff);
  }

  Serial.println("button3P");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void btn4Active()
{
  Serial.println("btnAct");
  // turn off button lights
  lightoffBtns();
  // turn on strip lights for every led except the button leds
  lightup();
  // turn on and off 5 times the button leds
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 73 + i;
      strip.setPixelColor(ledIndex, redC); // Red
      strip.show();
      delay(btnEffectOn);
    }
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 73 + i;
      strip.setPixelColor(ledIndex, blackC); // Red
      strip.show();
      delay(btnEffectOff);
    }
    delay(btnEffectOff);

    for (int k = 0; k < 3; k++)
    {
      int ledIndex = 73 + k;
      strip.setPixelColor(ledIndex, redC);
      strip.show();
      delay(btnEffectOn);
    }
  }

  // turn off the strip leds that create the effect

  for (int i = 41; i < 64; i++)
  {
    strip.setPixelColor(i, blackC);

    strip.show();
    delay(delayOff);
  }

  for (int i = 0; i < 33; i++)
  {
    strip.setPixelColor(i, blackC);

    strip.show();
    delay(delayOff);
  }

  Serial.println("button4P");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void btn5Active()
{
  Serial.println("btnAct");
  // turn off button lights
  lightoffBtns();
  // turn on strip lights for every led except the button leds
  lightup();
  // turn on and off 5 times the button leds
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 76 + i;
      strip.setPixelColor(ledIndex, redC); // Red
      strip.show();
      delay(btnEffectOn);
    }
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 76 + i;
      strip.setPixelColor(ledIndex, blackC); // Red
      strip.show();
      delay(btnEffectOff);
    }
    delay(btnEffectOff);

    for (int k = 0; k < 3; k++)
    {
      int ledIndex = 76 + k;
      strip.setPixelColor(ledIndex, redC);
      strip.show();
      delay(btnEffectOn);
    }
  }

  // turn off the strip leds that create the effect

  for (int i = 52; i < 64; i++)
  {
    strip.setPixelColor(i, blackC);

    strip.show();
    delay(delayOff);
  }

  for (int i = 0; i < 44; i++)
  {
    strip.setPixelColor(i, blackC);

    strip.show();
    delay(delayOff);
  }

  Serial.println("button5P");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void btn6Active()
{
  Serial.println("btnAct");
  // turn off button lights
  lightoffBtns();
  // turn on strip lights for every led except the button leds
  lightup();
  // turn on and off 5 times the button leds
  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 79 + i;
      strip.setPixelColor(ledIndex, redC); // Red
      strip.show();
      delay(btnEffectOn);
    }
    for (int i = 0; i < 3; i++)
    {
      int ledIndex = 79 + i;
      strip.setPixelColor(ledIndex, blackC); // Red
      strip.show();
      delay(btnEffectOff);
    }
    delay(btnEffectOff);

    for (int k = 0; k < 3; k++)
    {
      int ledIndex = 79 + k;
      strip.setPixelColor(ledIndex, redC);
      strip.show();
      delay(btnEffectOn);
    }
  }

  // turn off the strip leds that create the effect

  for (int i = 63; i < 64; i++)
  {
    strip.setPixelColor(i, blackC);
    strip.show();
    delay(delayOff);
  }

  for (int i = 0; i < 54; i++)
  {
    strip.setPixelColor(i, blackC);
    strip.show();
    delay(delayOff);
  }

  Serial.println("button6P");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void closeApp()
{
  Serial.println("closeApp");
}

void loop()
{

  // Check for incoming serial data
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n'); // Read the incoming data

    // Check if the received command is "Restart"
    if (command.equals("Restart"))
    {

      lightup();
      lightoffBtns();
    }
  }

  digitalWrite(LED_BUILTIN, LOW);

  bool s3State = digitalRead(s3);
  bool s5State = digitalRead(s5);

  if (s3State && s5State)
  {
    // Both s3 and s5 are HIGH
    if (startTime == 0)
    {
      // Start the timer
      startTime = millis();
    }
    else
    {
      // Check if 3 seconds have elapsed
      if (millis() - startTime >= duration)
      {
        shouldClose = true; // Set shouldClose to true
      }
    }
  }
  else
  {
    // Reset the timer if either s3 or s5 is not HIGH
    startTime = 0;
  }

  if (shouldClose)
  {
    closeApp();
  }

  b1P = (digitalRead(s1));
  delay(50);
  if (b1P)
  {
    btn1Active();
  }

  b2P = (digitalRead(s2));
  delay(50);
  if (b2P)
  {
    btn2Active();
  }

  b3P = (digitalRead(s3));
  delay(50);
  if (b3P)
  {
    btn3Active();
  }

  b4P = (digitalRead(s4));
  delay(50);
  if (b4P)
  {
    btn4Active();
  }

  b5P = (digitalRead(s5));
  delay(50);
  if (b5P)
  {
    btn5Active();
  }

  b6P = (digitalRead(s6));
  delay(50);
  if (b6P)
  {
    btn6Active();
  }

  digitalWrite(LED_BUILTIN, HIGH);
}
