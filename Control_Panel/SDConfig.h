// This is for saving configuration to the SD Card
#ifndef CONFIG_H
#define CONFIG_H

#include <SD.h>

#include "datatypes.h"
#include "User_Config.h"




class SDConfig {
  public:
    void init();

    void saveConfig();

    // Accessors and setters
    Time autoOnTime = { DEFAULT_AUTO_ON_HOUR, DEFAULT_AUTO_ON_MINUTE };
    unsigned int resumeDelay = DEFAULT_RESUME_DELAY; // 30 minute
    AlertMode alertMode = DEFAULT_ALERT_MODE;



  private:
    void setConfigDefaults(File cfg);
    void parseConfigFile(File cfg);
    void parseConfigLine(String key, String value);
};


SDConfig config = SDConfig();



#define CFG_FILE_NAME           "config"

// Keys for certain things
#define CFG_KEY_AUTO_ON_HOUR    "autoOnTimeHour"
#define CFG_KEY_AUTO_ON_MINUTE  "autoOnTimeMinute"
#define CFG_KEY_RESUME_DELAY    "resumeDelay"
#define CFG_KEY_ALERT_MODE      "alertMode"

#endif
