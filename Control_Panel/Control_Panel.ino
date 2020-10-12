#include "User_Config.h"
#include "SDConfig.h"
#include "System.h"
#include "Screen.h"
#include "datatypes.h"

extern SDConfig config;
extern Screen screen;
extern System sys;


void onMenuItem(TFT_HX8357 tft, void (*onExit)(void))
{

}

void setup() {
  Serial.begin(9600);

  config.init();
  sys.init();
  screen.init();

  screen.addMenuItem("Time", "Date and Time", onMenuItem);
  screen.addMenuItem("Auto-On Time", "Time to auto turn on", onMenuItem);
  screen.addMenuItem("Resume Delay", "Delay", onMenuItem);
  screen.addMenuItem("Alert Mode", "Mode", onMenuItem);
}

void loop() {
  sys.update();
  screen.render();
}
