#include "Strings.h"
#include "User_Config.h"
#include "SDConfig.h"
#include "Controls.h"
#include "Screen.h"
#include "System.h"
#include "datatypes.h"
#include "Clock.h"

extern SDConfig config;
extern Screen screen;
extern System sys;
extern Controls controls;
extern Clock clock;


void onMenuItem(TFT_HX8357 tft, void (*onExit)(void))
{

}



void setup() {
  Serial.begin(9600);

  clock.init();
  controls.init();
  config.init();
  sys.init();
  screen.init();

  screen.addMenuItem(MENU_TIME_LABEL, "Date and Time", onMenuItem);
  screen.addMenuItem(MENU_AUTO_ON_LABEL, "Time to auto turn on", onMenuItem);
  screen.addMenuItem(MENU_RESUME_DELAY_LABEL, "Delay", onMenuItem);
  screen.addMenuItem(MENU_ALERT_MODE_LABEL, "Mode", onMenuItem);
}

void loop() {
  sys.update();
  screen.render();
}
