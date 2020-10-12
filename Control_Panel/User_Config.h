#ifndef USER_CONFIG
#define USER_CONFIG



// Screen
#define SCREEN_WIDTH        480
#define SCREEN_HEIGHT       320

#define REFRESH_RATE        100
#define BOOT_SCREEN_DELAY   3000


// Defaults
#define DEFAULT_AUTO_ON_HOUR    22
#define DEFAULT_AUTO_ON_MINUTE  00
#define DEFAULT_RESUME_DELAY    2 // In minutes
#define DEFAULT_ALERT_MODE      0

#define MENU_TIMEOUT        10000 // 10 seconds on the menu without activity


// Colors
#define BG_COLOR                0xCE79
#define MENU_BG_COLOR   	    BG_COLOR //0x9CF3
#define MENU_SELECTED_COLOR     0x029F

#define ERROR_COLOR             0xF9C8;


// PINS
#define SD_CS   53

#define ENCODER_A_PIN       4
#define ENCODER_B_PIN       3
#define ENCODER_BTN         5

#define PRIMARY_BTN         2   // Button to turn on/off the system
#define EXTRA_BTN           8   // Extra button to make navigation/menus easier


// Functionality
#define USE_INTERRUPT_FOR_PRIMARY_BTN


#endif
