#define SRCLR 16
#define SRCLK 2
#define RCLK 5
#define SER 4

void setup()
{
  pinMode(SER, OUTPUT);
  pinMode(SRCLR, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);

  digitalWrite(SRCLR, LOW);
  digitalWrite(SRCLR, HIGH);
}

void loop()
{
  for (int i = 0; i < 100000000; i++)
  {
    printNum(i, 4);
  }
}
