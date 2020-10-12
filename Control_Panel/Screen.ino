#include "Screen.h"


TFT_HX8357 Screen = TFT_HX8357();

// Local variables



/**
 * Constructor
 */
Screen::Screen()
{
  menuItemsPushIndex = 0;
  menuItemSelectedIndex = 2;
  lastMenuItemSelected = -1;
}


/**
 * Initializer
 */
void Screen::init()
{
  tft = TFT_HX8357();
  tft.init();

  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  drawRAW("boot.raw", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, tft);
  timeAtInit = millis();

  screenState = Screen_Boot;

  lastRefresh = millis();
}


/**
 * Getter for the screen state
 */
SCREEN_STATE Screen::getState(void)
{
  return screenState;
}

/**
 * Setter for the screen state
 */
void Screen::setState(SCREEN_STATE newState)
{
  screenState = newState;
}


/**
 * Renders the current screen
 */
void Screen::render(void)
{
  if (screenState == Screen_Boot)
  {
    long timeSinceBootDisplay = millis() - timeAtInit;
    if (timeSinceBootDisplay < BOOT_SCREEN_DELAY) {
      delay(BOOT_SCREEN_DELAY - timeSinceBootDisplay);
      screenState = Screen_Home; // TODO: Change back to Screen_Home;
      clearScreen();
    }
    return;
  }

  if (screenState == Screen_Home)
    sys.processControls(); // Do all the time, even between refreshes

  if (!((millis() - lastRefresh) >= REFRESH_RATE))
    return;

  switch (screenState) {
    // Home Screen
    case Screen_Home:
      lastMenuItemSelected = -1;
      renderHomeScreen();
      break;

    // Settings menu
    case Screen_Menu:
      renderMenu();
      break;
  }

  lastRefresh = millis();
}


/**
 * Adds a new menu item
 */
void Screen::addMenuItem(String name, String description, void (*callbackFunction)(TFT_HX8357 tft, void (*onExit)(void)))
{
  if (menuItemsPushIndex >= 5)
    return;

  menuItems[menuItemsPushIndex] = {
    name,
    description,
    callbackFunction
  };

  menuItemsPushIndex++;
}




/**
 * Renders the home screen
 */
void Screen::renderHomeScreen()
{
  // Redraw the time
  tft.fillRect(380, 5, SCREEN_WIDTH, 22, BG_COLOR);
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(380, 5);

  DateTime time = clock.getTime();
  tft.print(time.twelveHour());
  tft.print(":");
  tft.print(time.minute());


  // Render icon based on system status
  if (sys.isTriggered())
  {

  }
  else if (sys.isAwaitingResume())
  {

  }
  else if (sys.isOn()) {
    drawRAW("lock.raw", 170, 70, 142, 217, tft);
  }
  else
  {
    drawRAW("unlocked.raw", 170, 70, 142, 217, tft);
  }

}



/**
 * Settings Menu
 */
void Screen::renderMenu()
{
  // Don't redraw the menu unless it has changed
  if (lastMenuItemSelected == menuItemSelectedIndex)
  {
    if ((millis() - lastMenuActivity) >= MENU_TIMEOUT)
    {
      screenState = Screen_Home;
      clearScreen();
      lastMenuItemSelected = -1;
    }


    // Testing
    if ((millis() - lastMenuActivity) >= 1500) {
      menuItemSelectedIndex++;
      if (menuItemSelectedIndex >= menuItemsPushIndex)
        menuItemSelectedIndex = 0;
    }

    return;
  }

  tft.setTextColor(TFT_BLACK);

  // Fill screen if first time showing (makes refreshing the display look better)
  if (lastMenuItemSelected == -1) {
    tft.fillRect(0, 0, MENU_WIDTH, SCREEN_HEIGHT, MENU_BG_COLOR);

    // Helper labels
    tft.setTextSize(2);
    tft.drawString(MENU_SELECT_LABEL, 5, 300, 1);
    tft.drawString(MENU_EXIT_LABEL, 425, 300, 1);
  }

  tft.setTextSize(MENU_FONT_SIZE);



  char buffer[20] = "";

  for (int i = 0; i < menuItemsPushIndex; i++) {
    menuItems[i].Name.toCharArray(buffer, menuItems[i].Name.length() + 1);

    if (i == menuItemSelectedIndex)
    {
      tft.setTextColor(TFT_WHITE);
      tft.fillRect(0, i * MENU_ROW_HEIGHT, MENU_WIDTH, MENU_ROW_HEIGHT, MENU_SELECTED_COLOR);
    }
    else
    {
      tft.setTextColor(TFT_BLACK);
      tft.fillRect(0, i * MENU_ROW_HEIGHT, MENU_WIDTH, MENU_ROW_HEIGHT, MENU_BG_COLOR);
    }

    tft.drawCentreString(buffer, SCREEN_WIDTH / 2,  10 + (i * MENU_ROW_HEIGHT), 4);
  }

  lastMenuItemSelected = menuItemSelectedIndex;
  lastMenuActivity = millis();
}




/**
 * Clears the screen
 */
void Screen::clearScreen()
{
  tft.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BG_COLOR);
}


/*
int hour = 11;
int minute = 0;
bool drawn = false;

void Screen::homeScreen() {
  long timeSinceBootDisplay = millis() - timeAtInit;
  if (timeSinceBootDisplay < BOOT_SCREEN_DELAY) {
    delay(BOOT_SCREEN_DELAY - timeSinceBootDisplay);
  }

  if (!drawn)
    tft.fillScreen(BG_COLOR);

  tft.fillRect(380, 5, 420, 22, BG_COLOR);

  // TODO: time from RTC
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(380, 5);
  tft.print(hour);
  tft.print(":");
  if (minute < 10)
    tft.print("0");
  tft.print(minute);

  if (!drawn) {
    drawRAW("lock.raw", 170, 70, 142, 217, tft);
    drawn = true;
  }

  minute++;
  if (minute >= 60)
   {
    hour++;
    minute =0;

    if (hour >= 24)
      hour = 0;
   }

}

*/




/**
 * Helpers
 */


#define RBUFF_SIZE 256

void drawRAW(char *filename, int16_t x, int16_t y, int16_t rawWidth, int16_t rawHeight, TFT_HX8357 tft) {
  File     rawFile;
  uint8_t  sdbuffer[2 * RBUFF_SIZE];   // SD read pixel buffer (16 bits per pixel)
  Serial.println(filename);

  // Check file exists and open it
  if ((rawFile = SD.open(filename)) == NULL) {
    Serial.println(F(" File not found"));
    return;
  }

  // Prepare the TFT screen area to receive the data
  tft.setWindow(x, y, x + rawWidth - 1, y + rawHeight - 1);

  // Work out how many whole buffers to send
  uint16_t nr = ((long)rawHeight * rawWidth)/RBUFF_SIZE;
  while(nr--) {
    rawFile.read(sdbuffer, sizeof(sdbuffer));
    tft.pushColors(sdbuffer, RBUFF_SIZE);
  }

  // Send any partial buffer
  nr = ((long)rawHeight * rawWidth)%RBUFF_SIZE;
  if (nr) {
    rawFile.read(sdbuffer, nr<<1); // We load  2 x nr bytes
    tft.pushColors(sdbuffer, nr);  // We send nr 16 bit pixels
  }

  // Close the file
  rawFile.close();
}
