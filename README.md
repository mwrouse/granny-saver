# Granny Saver
Granny Saver is an Arduino based control panel for simple PIR-alarm combinations such as [this one](https://www.amazon.com/WJLING-Wireless-Driveway-Security-Business/dp/B07SV2WG3W).

It improves functionality by adding the ability to quickly turn on/off the sensor(s) from one central location and can turn on/off on a schedule.

The original purpose was for monitoring elderly who are a fall-risk while they sleep.


This project requires soldering.

## Setup
Using this product requires that at least two of the PIR sensors be sacrificed. One will become a new transmitter (to the control panel) and the other will be used by the control panel to trigger the alarms.

### New Transmitter
The new transmitter will be Arduino based, it will improve the usability of the PIR sensors by implementing things like: warm up delay (no PIR trigger for first minute after power on), and delays between triggers.



### Control Panel