#include "Clock.h"


/**
 * Initialize the clock
 */
void Clock::init(void)
{
    rtc = RTC_DS3231();

    if (!rtc.begin())
    {
        Serial.println("Failed to initialize RTC");
        return;
    }

    if (rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    rtc.disable32K();

    disableAlarm(AUTO_ON_ALARM);
    disableAlarm(AUTO_ON_ALARM);
}


/**
 * Check if time is set
 */
bool Clock::hasTimeSet(void)
{
    return true;
}


/**
 * Returns the current time
 */
DateTime Clock::getTime(void)
{
    return rtc.now();
}


/**
 * Sets alarms on the rtc
 */
void Clock::setAlarm(uint8_t alarm, DateTime time)
{
    if (alarm == AUTO_ON_ALARM)
    {
        rtc.setAlarm1(time, DS3231_A1_Hour);
    }
    else if (alarm == RESUME_ALARM)
    {
        rtc.setAlarm2(time, DS3231_A2_Hour);
    }
}

void Clock::clearAlarm(uint8_t alarm)
{
    rtc.clearAlarm(alarm);
}

void Clock::disableAlarm(uint8_t alarm)
{
    rtc.clearAlarm(alarm);
    rtc.disableAlarm(alarm);
}

bool Clock::isAlarmTriggered(uint8_t alarm)
{
    return rtc.alarmFired(alarm);
}