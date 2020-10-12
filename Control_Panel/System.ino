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

}


/**
 * Check for alarm to be triggered or to be forced off
 * Also sends signal to alarms if set
 */
void System::update()
{
    // TODO: Check if triggered

    // Send alert if triggered
    if (alarmStatus == Alarm_Triggered)
    {
        // TODO: Check if turned off


        #ifdef ALERT_UNTIL_TURNED_OFF
            sendAlert();
        #else
            if (!alertSentSinceTriggered && alarmStatus == Alarm_Triggered)
            {
                sendAlert();
                alertSentSinceTriggered = true;
            }
        #endif
    }

}


/**
 * Sends an alert to the transmitter
 */
void System::sendAlert()
{
    // TODO: Send alert
}


/**
 * Getter for the state of the alarm
 */
bool System::isTriggered()
{
    return alarmStatus == Alarm_Triggered;
}


/**
 * Getter for the system status
 */
SYSTEM_STATUS System::getStatus()
{
    return status;
}