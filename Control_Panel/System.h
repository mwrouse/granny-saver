#ifndef SYSTEM_H
#define SYSTEM_H

#include "SDConfig.h";
extern SDConfig config;


enum SYSTEM_STATUS
{
    System_On,
    System_Off,
    System_AutoOn,
};


enum ALARM_STATUS
{
    Alarm_Off,
    Alarm_Triggered
};



class System
{
    public:
        System();
        void init();
        void update(); // Triggered every loop

        SYSTEM_STATUS getStatus();
        bool isTriggered();


    private:
        SYSTEM_STATUS status;
        ALARM_STATUS alarmStatus;
        bool alertSentSinceTriggered;


        void sendAlert();
};


System sys = System();

#endif