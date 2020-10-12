#ifndef SCREEN_H
#define SCREEN_H

#include "User_Config.h"
#include "datatypes.h"

#include <TFT_HX8357.h>

#include "System.h"
extern System sys;

void drawRAW(char *filename, int16_t x, int16_t y, int16_t rawWidth, int16_t rawHeight);


// Config
#define MENU_FONT_SIZE          2
#define MENU_ROW_HEIGHT         60
#define MENU_WIDTH              SCREEN_WIDTH


enum SCREEN_STATE
{
  Screen_Boot,
  Screen_Home,
  Screen_Menu,
};



struct MenuItem {
  String Name;
  String Description;
  void (*onSelected)(TFT_HX8357 tft, void (*onExit)(void));
};



/**
 * Wrapper around the TFT_HX8357 library
 */
class Screen {
  public:
    Screen(void);
    void init(void);
    void render(void);

    void addMenuItem(String name, String description, void (*callbackFunction)(TFT_HX8357 tft, void (*onExit)(void)));

   private:
    unsigned long timeAtInit;
    unsigned long lastRefresh;

    TFT_HX8357 tft;
    SCREEN_STATE screenState;

    void clearScreen();
    void renderHomeScreen();
    void renderMenu();

    MenuItem menuItems[10];
    int menuItemsPushIndex;
    int menuItemSelectedIndex;
    unsigned long lastMenuActivity;
    unsigned int lastMenuItemSelected;
};

Screen screen = Screen();

#endif
