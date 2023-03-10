#include "RTClib.h"

#define HYPHEN B00000001
#define NONE B00000000
#define SRCLR 16
#define SRCLK 2
#define RCLK 10
#define SER 9
// 表示切替
#define INTERRUPT_PIN 1
#define DATE_LED 14
#define TIME_LED 12
#define TEMP_LED 13
#define HUM_LED 15
#define HPA_LED 3

typedef int Digits[8];

// 0 is date
// 1 is time
// 2 is temp
// 3 is humidity
// 4 is pressure
int selector = 0;

void handleInterrupt()
{
  // off all
  digitalWrite(DATE_LED, LOW);
  digitalWrite(TIME_LED, LOW);
  digitalWrite(TEMP_LED, LOW);
  digitalWrite(HUM_LED, LOW);
  digitalWrite(HPA_LED, LOW);
  selector = selector + 1;
  switch (selector)
  {
  case 0:
    // 誰もここに到達しない
    break;
  case 1:
    // time
    digitalWrite(TIME_LED, HIGH);
    break;
  case 2:
    // temp
    digitalWrite(TEMP_LED, HIGH);
    break;
  case 3:
    digitalWrite(HUM_LED, HIGH);
    break;
  case 4:
    digitalWrite(HPA_LED, HIGH);
    break;
  default:
    selector = 0;
    // date
    digitalWrite(DATE_LED, HIGH);
    break;
  }
}

void setup()
{
  // Serial.begin(115200);
  pinMode(SER, OUTPUT);
  pinMode(SRCLR, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  // 割り込み
  pinMode(DATE_LED, OUTPUT);
  pinMode(TIME_LED, OUTPUT);
  pinMode(TEMP_LED, OUTPUT);
  pinMode(HUM_LED, OUTPUT);
  pinMode(HPA_LED, OUTPUT);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);

  digitalWrite(SRCLR, LOW);
  digitalWrite(SRCLR, HIGH);
  digitalWrite(DATE_LED, HIGH);
  setupRtc();
  setupBME280();
  printHello();
}

void loop()
{
  // 割り込みで実装しようとして諦めた、表示切り替え処理
  int duration = 0;
  while (digitalRead(INTERRUPT_PIN) == LOW)
  {
    printLoading();
    duration++;
    if (duration > 2)
    {
      printHello();
      return;
    }
  }
  if (duration > 0)
  {
    handleInterrupt();
  }
  ///////////////////////////////////////////////
  switch (selector)
  {
  case 0:
    // date
    printDate();
    break;
  case 1:
    // time
    printTime();
    break;
  case 2:
    // temp
    printBME280Data(0);
    break;
  case 3:
    printBME280Data(1);
    break;
  case 4:
    printBME280Data(2);
    break;
  default:
    selector = 0;
    break;
  }
}
