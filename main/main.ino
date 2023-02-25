#define SRCLR 16
#define SRCLK 2
#define RCLK 10
#define SER 9
#define SERIAL_BAUD 115200

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
  for (int i = 0; i < 100000000; i++)
  {
    printNum(i, 4);
  }
}
