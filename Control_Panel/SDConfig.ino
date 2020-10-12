#include "SDConfig.h"





void SDConfig::init() {
  // Init SD Card
  if (!SD.begin(SD_CS)) {
    Serial.println("Failed to init SD Card");
    return;
  }

  SD.remove(CFG_FILE_NAME); // TODO: Remove this once everything is going
  File configFile;

  // Create config if needed
  if (!SD.exists(CFG_FILE_NAME)) {
    configFile = SD.open(CFG_FILE_NAME, FILE_WRITE);
    setConfigDefaults(configFile);
    configFile.close();
  }

  // Read configuration
  configFile = SD.open(CFG_FILE_NAME, FILE_READ);
  parseConfigFile(configFile);
  configFile.close();
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
  if (key == CFG_KEY_AUTO_ON_HOUR) {
    autoOnTime.Hour = value.toInt();
  }
  else if (key == CFG_KEY_AUTO_ON_MINUTE) {
    autoOnTime.Minute = value.toInt();
  }
  else if (key == CFG_KEY_RESUME_DELAY)
  {
    resumeDelay = value.toInt();
  }
  else if (key == CFG_KEY_ALERT_MODE)
  {
    alertMode = value.toInt();
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
  writeCfgValue(cfg, CFG_KEY_AUTO_ON_HOUR, DEFAULT_AUTO_ON_HOUR);
  writeCfgValue(cfg, CFG_KEY_AUTO_ON_MINUTE, DEFAULT_AUTO_ON_MINUTE);
  writeCfgValue(cfg, CFG_KEY_RESUME_DELAY, DEFAULT_RESUME_DELAY);
  writeCfgValue(cfg, CFG_KEY_ALERT_MODE, DEFAULT_ALERT_MODE);
}


/**
 * Writes updated values to the config file
 */
void SDConfig::saveConfig() {
  File cfg = SD.open(CFG_FILE_NAME, FILE_WRITE);
  cfg.seek(0);

  writeCfgValue(cfg, CFG_KEY_AUTO_ON_HOUR, autoOnTime.Hour);
  writeCfgValue(cfg, CFG_KEY_AUTO_ON_MINUTE, autoOnTime.Minute);
  writeCfgValue(cfg, CFG_KEY_RESUME_DELAY, resumeDelay);
  writeCfgValue(cfg, CFG_KEY_ALERT_MODE, alertMode);

  cfg.close();
}



/**
 * Helpers for writing cfg values from file
 */
void writeCfgValue(File cfg, String key, String value)
{
  cfg.print(key);
  cfg.print(":");
  cfg.println(value);
}


void writeCfgValue(File cfg, String key, unsigned int value)
{
  cfg.print(key);
  cfg.print(":");
  cfg.println(value);
}

void writeCfgValue(File cfg, String key, int value)
{
  cfg.print(key);
  cfg.print(":");
  cfg.println(value);
}