#ifndef CLOCK_H
#define CLOCK_H

#include <RTClib.h>
#include "User_Config.h"
#include "datatypes.h"


// Numbers for the RTC alarms
#define AUTO_ON_ALARM       1
#define RESUME_ALARM        2


class Clock {
    public:
        void init(void);

        bool hasTimeSet(void);

        DateTime getTime(void);

        void setAlarm(uint8_t alarmNumber, DateTime time);
        bool isAlarmTriggered(uint8_t alarmNumber);

        void clearAlarm(uint8_t alarmNumber);
        void disableAlarm(uint8_t alarmNumber);

    private:
        RTC_DS3231 rtc;
};

Clock clock = Clock();

#endif