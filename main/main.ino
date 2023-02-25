#include "RTClib.h"

#define HYPHEN B00000001
#define NOTHING B00000000
#define SRCLR 16
#define SRCLK 2
#define RCLK 10
#define SER 9
#define SERIAL_BAUD 115200

typedef int Digits[8];

void setup()
{
  Serial.begin(SERIAL_BAUD);
  pinMode(SER, OUTPUT);
  pinMode(SRCLR, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);

  digitalWrite(SRCLR, LOW);
  digitalWrite(SRCLR, HIGH);
  setupRtc();
  setupBME280();
}

void loop()
{
  printTime();
}
