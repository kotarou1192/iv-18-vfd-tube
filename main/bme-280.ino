#include <BME280I2C.h>

BME280I2C bme; // Default : forced mode, standby time = 1000 ms
               // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

//////////////////////////////////////////////////////////////////
void setupBME280()
{
  while (!bme.begin())
  {
    printErr();
  }
}

//////////////////////////////////////////////////////////////////
// 0 is temp
// 1 is humidity
// 2 is pressure
void printBME280Data(int select)
{
  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.read(pres, temp, hum, tempUnit, presUnit);
  int hpa = (int)pres;

  // 数値が39.9-40.0とかを行き来すると、なんて表示されているのかわからない
  // ループして待ってあげることで、更新頻度を下げる。
  for (int i = 0; i < 200; i++)
  {
    // スムーズに切り替えるためのスイッチ監視
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
      return;
    }
    ////////////////////////////////////////
    switch (select)
    {
    case 0:
      printNum((int)(temp * 100) / 10, 1);
      break;
    case 1:
      printNum((int)(hum * 100) / 10, 1);
      break;
    case 2:
      printNum(hpa / 10, 1);
      break;
    default:
      printErr();
    }
  }
}
