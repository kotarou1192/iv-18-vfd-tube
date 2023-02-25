void printDate()
{
  DateTime now = rtc.now();

  int year = now.year();
  int splittedYear[2] = {0, 0};
  splitDigit(year % 100, splittedYear);
  int month = now.month();
  int splittedMonth[2] = {0, 0};
  splitDigit(month, splittedMonth);
  int day = now.day();
  int splittedDay[2] = {0, 0};
  splitDigit(day, splittedDay);
  Digits datetime = {numToSegment(splittedDay[0]),
                     numToSegment(splittedDay[1]),
                     HYPHEN,
                     numToSegment(splittedMonth[0]),
                     numToSegment(splittedMonth[1]),
                     HYPHEN,
                     numToSegment(splittedYear[0]),
                     numToSegment(splittedYear[1])};

  printDigits(datetime);
}

void printTime()
{
  DateTime now = rtc.now();

  int hour = now.hour();
  int splittedHour[2] = {0, 0};
  splitDigit(hour % 100, splittedHour);
  int minute = now.minute();
  int splittedMinute[2] = {0, 0};
  splitDigit(minute, splittedMinute);
  int second = now.second();
  int splittedSecond[2] = {0, 0};
  splitDigit(second, splittedSecond);
  Digits datetime = {numToSegment(splittedSecond[0]),
                     numToSegment(splittedSecond[1]),
                     HYPHEN,
                     numToSegment(splittedMinute[0]),
                     numToSegment(splittedMinute[1]),
                     HYPHEN,
                     numToSegment(splittedHour[0]),
                     numToSegment(splittedHour[1])};

  printDigits(datetime);
}

void printDigits(Digits values)
{
  for (int i = 0; i < 8; i++)
  {
    // off
    digitalWrite(RCLK, LOW);
    shiftOut(SER, SRCLK, LSBFIRST, numToDigit(i));
    shiftOut(SER, SRCLK, LSBFIRST, values[i]);
    // on
    digitalWrite(RCLK, HIGH);
    delay(1);
  }
}

void printNum(int num, int dotDigit)
{
  Digits nums = {-1, -1, -1, -1, -1, -1, -1, -1};
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
    delay(1);
  }
}

void printErr()
{
  const int e = B10101101;
  const int r = B10000001;
  const int o = B11100001;
  Digits err = {NONE, r, o, r, r, e, NONE, NONE};
  printDigits(err);
}

void printHyphen()
{
  Digits line = {HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN};
  printDigits(line);
}

void printHello()
{
  const int h = B11000111;
  const int e = B10101101;
  const int l = B10100100;
  const int o = B11101110;
  int completed = 1;
  int cnt = 0;
  int times = 0;
  int sleeper = 0;
  Digits arr = {HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN, HYPHEN};
  const Digits hello = {HYPHEN, o, l, l, e, h};
  while (times < 14)
  {
    printDigits(arr);
    cnt++;
    if (cnt % 20 == 0)
    {
      do
      {
        sleeper++;
        printDigits(arr);
      } while (times == 7 && sleeper < 70);
      times++;
      for (int j = times; j > 0; j--)
      {
        arr[(times - j) > 7 ? j - times : times - j] = hello[j < 6 && (times - j) < 8 ? 6 - j : 0];
      }
    }
  }

  digitalWrite(SRCLR, LOW);
  digitalWrite(SRCLR, HIGH);
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
    return NONE;
    break;
  }
}
