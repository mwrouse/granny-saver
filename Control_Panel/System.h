#ifndef SYSTEM_H
#define SYSTEM_H

#include "datatypes.h"
#include "User_Config.h";
#include "SDConfig.h";
#include "Controls.h"
#include "Clock.h"

extern SDConfig config;
extern Controls controls;
extern Clock clock;


enum SYSTEM_STATUS
{
    System_On,
    System_Off,
    System_Resume,
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
        void processControls(); // Used to only enable the controls for the system on the home screen

        SYSTEM_STATUS getStatus();
        bool isOn();
        bool isAwaitingResume();
        bool isTriggered();

        void turnOn();
        void turnOff();
        void startResumeWait();

    private:
        SYSTEM_STATUS status;
        ALARM_STATUS alarmStatus;
        bool alertSentSinceTriggered;

        void sendAlert();

};


System sys = System();

#endif