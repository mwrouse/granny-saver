#include "System.h"


/**
 * Constructor
 */
System::System()
{
    status = System_On; // On by default in-case of power outage
    alarmStatus = Alarm_Off;
    alertSentSinceTriggered = false;
}

/**
 * To do things if ever needed
 */
void System::init()
{
    // TODO: Set auto-back on time from config
    if (config.autoOnTime.Hour != -1 && config.autoOnTime.Minute != -1) {
        DateTime autoOnTime = DateTime(2020, 10, 10, config.autoOnTime.Hour, config.autoOnTime.Minute, 0);
        clock.setAlarm(AUTO_ON_ALARM, autoOnTime);
    }

    //startResumeWait();
}


/**
 * Check for alarm to be triggered or to be forced off
 * Also sends signal to alarms if set
 */
void System::update()
{
    // Handle resuming
    if (isAwaitingResume())
    {
        // Check if time is up
        if (clock.isAlarmTriggered(RESUME_ALARM))
        {
            turnOn();
        }
        else {
            if (controls.isPrimaryButtonPressed()) {
                turnOn();
            }
            else if (controls.isSecondaryButtonPressed()) {
                turnOff();
            }
        }
    }

    // Automatically turn back on at a set time
    if (!isOn() && clock.isAlarmTriggered(AUTO_ON_ALARM))
    {
        turnOn();
        clock.clearAlarm(AUTO_ON_ALARM);
    }

    // TODO: Check if triggered, update timeAtLastTrigger


    // Don't do anything if turned off
    if (status == System_Off)
        return;

    // TODO: Auto go to home screen if triggered



    // Send alert if triggered
    if (isTriggered())
    {
        if (config.alertMode == AlertMode_Continuous) {
            // Continuous alert mode (keeps ringing until turned off)
            sendAlert();
        }
        else if (!alertSentSinceTriggered) {
            // Ring once
            sendAlert();
        }
    }

}



/**
 * Used to check the controls that will turn on/off the system on the home screen
 */
void System::processControls(void)
{
    if (controls.isPrimaryButtonPressed())
    {
        if (isTriggered())
        {
            startResumeWait();
        }
        else {
            // Standard state switching
            if (status == System_Off || status == System_Resume)
                turnOn();
            else if (status == System_On)
                turnOff();
        }
    }
}


/**
 * Sends an alert to the transmitter
 */
void System::sendAlert()
{
    // TODO: Send alert
    alertSentSinceTriggered = true;
}


/**
 * Getter for the state of the alarm
 */
bool System::isTriggered()
{
    return  alarmStatus == Alarm_Triggered;
}


/**
 * Getter for the system status
 */
SYSTEM_STATUS System::getStatus()
{
    return status;
}

bool System::isOn()
{
    return status == System_On;
}

bool System::isAwaitingResume()
{
    return status == System_Resume;
}


/**
 * Turn the system on
 */
void System::turnOn(void)
{
    status = System_On;
    alarmStatus = Alarm_Off;

    alertSentSinceTriggered = false;

    clock.disableAlarm(RESUME_ALARM);
}

/**
 * Turn the system off
 */
void System::turnOff(void)
{
    status = System_Off;
    alarmStatus = Alarm_Off;

    alertSentSinceTriggered = false;

    clock.disableAlarm(RESUME_ALARM);
}

/**
 * Start the system waiting for resume
 */
void System::startResumeWait(void)
{
    if (status == System_Resume)
        return;

    // Turn off immediately (No Resume)
    if (config.resumeDelay == -1) {
        turnOff();
        return;
    }

    // Turn on immediately (No Delay)
    if (config.resumeDelay == 0) {
        turnOn();
        return;
    }

    status = System_Resume;

    // Set resume time clock
    DateTime triggerTime = clock.getTime() + TimeSpan(config.resumeDelay * 60);
    clock.setAlarm(RESUME_ALARM, triggerTime);
}



