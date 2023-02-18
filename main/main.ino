#define SRCLR 16
#define SRCLK 2
#define RCLK 5
#define SER 4

void printNum(int num, int dotDigit)
{
  int nums[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
  splitDigit(num, nums);
  for (int i = 0; i < 8; i++)
  {
    if (nums[i] == -1)
      break;
    // off
    digitalWrite(RCLK, LOW);
    shiftOut(SER, SRCLK, LSBFIRST, numToDigit(i));
    shiftOut(SER, SRCLK, LSBFIRST, setDotToNum(numToSegment(nums[i]), i == dotDigit));
    // on
    digitalWrite(RCLK, HIGH);
    delay(3);
  }
}

void splitDigit(int nums, int *result)
{
  for (int i = 0; i < 8; i++)
  {
    int first = nums % 10;
    result[i] = first;
    if (first == nums)
      break;
    nums = (nums - first) / 10;
  }
}

int numToDigit(int num)
{
  const int a = B00000001;
  const int b = B10000000;
  const int c = B00000010;
  const int d = B01000000;
  const int e = B00000100;
  const int f = B00100000;
  const int g = B00010000;
  const int h = B00001000;

  switch (num)
  {
  case 0:
    return a;
    break;
  case 1:
    return b;
    break;
  case 2:
    return c;
    break;
  case 3:
    return d;
    break;
  case 4:
    return e;
    break;
  case 5:
    return f;
    break;
  case 6:
    return g;
    break;
  case 7:
    return h;
    break;
  default:
    return B11111111;
    break;
  }
}

int setDotToNum(int n, bool isDot)
{
  const int dot = B00010000;
  if (isDot)
    return n | dot;

  return n;
}

int numToSegment(int num)
{
  // 左下,右下,下,点,上,左上,右上,中
  const int zero = B11101110;
  const int one = B01000010;
  const int two = B10101011;
  const int three = B01101011;
  const int four = B01000111;
  const int five = B01101101;
  const int six = B11101101;
  const int seven = B01001010;
  const int eight = B11101111;
  const int nine = B01101111;
  const int none = B00000000;

  switch (num)
  {
  case 0:
    return zero;
    break;
  case 1:
    return one;
    break;
  case 2:
    return two;
    break;
  case 3:
    return three;
    break;
  case 4:
    return four;
    break;
  case 5:
    return five;
    break;
  case 6:
    return six;
    break;
  case 7:
    return seven;
    break;
  case 8:
    return eight;
    break;
  case 9:
    return nine;
    break;
  default:
    return none;
    break;
  }
}

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
