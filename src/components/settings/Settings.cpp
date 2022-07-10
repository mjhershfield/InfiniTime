#include "components/settings/Settings.h"
#include <cstdlib>
#include <cstring>
#include "displayapp/lv_pinetime_theme.h"
#include "displayapp/Colors.h"

using namespace Pinetime::Controllers;

Settings::Settings(Pinetime::Controllers::FS& fs) : fs {fs} {
}

void Settings::Init() {

  // Load default settings from Flash
  LoadSettingsFromFile();
  updateTheme();

}

Settings::ColorScheme Settings::getTheme() const{
  return settings.themes[settings.selectedTheme];
}

Settings::ColorScheme Settings::getTheme(uint8_t themeNumber) const {
  return settings.themes[themeNumber];
}

void Settings::setTheme(ColorScheme newScheme, uint8_t themeNumber)
{
  if (themeNumber < 3) {
    settings.themes[themeNumber] = newScheme;
    settingsChanged = true;
    updateTheme();
  }
}

void Settings::setTheme(ColorScheme newScheme)
{
    settings.themes[settings.selectedTheme] = newScheme;
    settingsChanged = true;
    updateTheme();
}

uint8_t Settings::getThemeNumber() const {
  return settings.selectedTheme;
}

void Settings::setThemeNumber(uint8_t num) {
  if (num < 3) {
    settings.selectedTheme = num;
    settingsChanged = true;
    updateTheme();
  }
}

void Settings::updateTheme() const {
  const ColorScheme& theme = getTheme();
  pt_update_theme(Pinetime::Applications::Convert(theme.primary, theme.primaryTint), 
                  Pinetime::Applications::Convert(theme.secondary, theme.secondaryTint),
                  Pinetime::Applications::Convert(theme.surface, theme.surfaceTint),
                  Pinetime::Applications::Convert(theme.background, theme.backgroundTint));
}

void Settings::SaveSettings() {

  // verify if is necessary to save
  if (settingsChanged) {
    SaveSettingsToFile();
  }
  settingsChanged = false;
}

void Settings::LoadSettingsFromFile() {
  SettingsData bufferSettings;
  lfs_file_t settingsFile;

  if ( fs.FileOpen(&settingsFile, "/settings.dat", LFS_O_RDONLY) != LFS_ERR_OK) {
    return;
  }
  fs.FileRead(&settingsFile, reinterpret_cast<uint8_t*>(&bufferSettings), sizeof(settings));
  fs.FileClose(&settingsFile);
  if ( bufferSettings.version == settingsVersion ) {
    settings = bufferSettings;
  }
}

void Settings::SaveSettingsToFile() {
  lfs_file_t settingsFile;

  if ( fs.FileOpen(&settingsFile, "/settings.dat", LFS_O_WRONLY | LFS_O_CREAT) != LFS_ERR_OK) {
    return;
  }
  fs.FileWrite(&settingsFile, reinterpret_cast<uint8_t*>(&settings), sizeof(settings));
  fs.FileClose(&settingsFile);
}
