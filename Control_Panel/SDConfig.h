// This is for saving configuration to the SD Card
#ifndef CONFIG_H
#define CONFIG_H

#include <SD.h>

#include "datatypes.h"




class SDConfig {
  public:
    void init();
    Time autoOnTime = { -1, -1 };


  private:
    void setConfigDefaults(File cfg);
    void parseConfigFile(File cfg);
    void parseConfigLine(String key, String value);
};


SDConfig config = SDConfig();

#endif
