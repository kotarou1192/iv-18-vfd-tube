RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setupRtc()
{
  if (!rtc.begin())
  {
    // Serial.println("Couldn't find RTC");
    // Serial.flush();
    while (1)
      printError();
  }
  // DO NOT ADJUST TIME AUTOMATICALY
  if (rtc.lostPower())
  {
    // Serial.println("RTC lost power, let's set the time!");
    //  When time needs to be set on a new device, or after a power loss, the
    //  following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}
