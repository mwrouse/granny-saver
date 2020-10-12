#include "SDConfig.h"



void SDConfig::init() {
  // Init SD Card
  if (!SD.begin(SD_CS)) {
    Serial.println("Failed to init SD Card");
    return;
  }

  SD.remove("config"); // TODO: Remove this once everything is going
  File configFile;

  // Create config if needed
  if (!SD.exists("config")) {
    configFile = SD.open("config", FILE_WRITE);
    setConfigDefaults(configFile);
    configFile.close();
  }

  // Read configuration
  configFile = SD.open("config", FILE_READ);
  parseConfigFile(configFile);
}



/**
 * Reads the config file and gets settings from it
 */
void SDConfig::parseConfigFile(File cfg) {
  cfg.seek(0);

  char characterRead = NULL;

  Serial.println("Reading Config from SD Card");

  bool isReadingKey = true;
  String key = "";
  String value = "";

  while (cfg.available()) {
    characterRead = cfg.read();

    if (characterRead != '\n') {
      if (isReadingKey && characterRead == ':') {
        isReadingKey = false;
      }
      else if (isReadingKey) {
        key = key + characterRead;
      }
      else {
        value = value + characterRead;
      }
    }
    else {
      Serial.println(key + " = " + value);
      parseConfigLine(key, value);

      isReadingKey = true;
      key = "";
      value = "";
    }
  }
}

/**
 * Actually parses a single line from a config value entry
 */
void SDConfig::parseConfigLine(String key, String value) {
  if (key == "autoOnTimeHour" || key == "failSafeOnTimeHour") {
    autoOnTime.Hour = value.toInt();
  }
  else if (key == "autoOnTimeMinute" || key == "failSafeOnTimeMinute") {
    autoOnTime.Minute = value.toInt();
  }
  else {
    Serial.println("Unknown config key " + key);
  }

}


/**
 * Sets the default configuratoin
 */
void SDConfig::setConfigDefaults(File cfg) {
  Serial.println("Creating Configuration");

  cfg.seek(0);
  cfg.println("autoOnTimeHour:22");
  cfg.println("autoOnTimeMinute:00");
}
