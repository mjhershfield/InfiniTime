#pragma once
#include <cstdint>
#include <bitset>
#include "components/brightness/BrightnessController.h"
#include "components/fs/FS.h"
#include <lvgl/src/lv_misc/lv_color.h>

namespace Pinetime {
  namespace Controllers {
    class Settings {
    public:
      enum class ClockType : uint8_t { H24, H12 };
      enum class Notification : uint8_t { ON, OFF };
      enum class ChimesOption : uint8_t { None, Hours, HalfHours };
      enum class WakeUpMode : uint8_t {
        SingleTap = 0,
        DoubleTap = 1,
        RaiseWrist = 2,
        Shake = 3,
      };
      enum class Colors : uint8_t {
        White,
        Silver,
        Gray,
        Black,
        Red,
        Maroon,
        Yellow,
        Olive,
        Lime,
        Green,
        Cyan,
        Teal,
        Blue,
        Navy,
        Magenta,
        Purple,
        Orange
      };

      struct ColorScheme {
        lv_color_t background = lv_color_hex(0x000000);
        lv_color_t accentPrimary = lv_color_hex(0xFFA500);
        lv_color_t accentSecondary = lv_color_hex(0x00FFE7);
        lv_color_t buttonDefault = lv_color_hex(0x111111);
        lv_color_t buttonDisabled = lv_color_hex(0xAEAEAE);
        lv_color_t success = lv_color_hex(0x008000);
        lv_color_t pause = lv_color_hex(0xFFFF00);
        lv_color_t stop = lv_color_hex(0xFF0000);
        lv_color_t textDefault = lv_color_hex(0xFFFFFF);
      };
      struct PineTimeStyle {
        Colors ColorTime = Colors::Teal;
        Colors ColorBar = Colors::Teal;
        Colors ColorBG = Colors::Black;
      };

      Settings(Pinetime::Controllers::FS& fs);

      void Init();
      void SaveSettings();

      void SetClockFace(uint8_t face) {
        if (face != settings.clockFace) {
          settingsChanged = true;
        }
        settings.clockFace = face;
      };
      uint8_t GetClockFace() const {
        return settings.clockFace;
      };

      void SetChimeOption(ChimesOption chimeOption) {
        if (chimeOption != settings.chimesOption) {
          settingsChanged = true;
        }
        settings.chimesOption = chimeOption;
      };
      ChimesOption GetChimeOption() const {
        return settings.chimesOption;
      };

      void SetPTSColorTime(Colors colorTime) {
        if (colorTime != settings.PTS.ColorTime)
          settingsChanged = true;
        settings.PTS.ColorTime = colorTime;
      };
      Colors GetPTSColorTime() const {
        return settings.PTS.ColorTime;
      };

      void SetPTSColorBar(Colors colorBar) {
        if (colorBar != settings.PTS.ColorBar)
          settingsChanged = true;
        settings.PTS.ColorBar = colorBar;
      };
      Colors GetPTSColorBar() const {
        return settings.PTS.ColorBar;
      };

      void SetPTSColorBG(Colors colorBG) {
        if (colorBG != settings.PTS.ColorBG)
          settingsChanged = true;
        settings.PTS.ColorBG = colorBG;
      };
      Colors GetPTSColorBG() const {
        return settings.PTS.ColorBG;
      };

      lv_color_t getBackgroundColor() const {
        return settings.colorScheme.background;
      };

      lv_color_t getAccentPrimaryColor() const {
        return settings.colorScheme.accentPrimary;
      };

      lv_color_t getAccentSecondaryColor() const {
        return settings.colorScheme.accentSecondary;
      };

      lv_color_t getButtonDefaultColor() const {
        return settings.colorScheme.buttonDefault;
      };

      lv_color_t getButtonDisabledColor() const {
        return settings.colorScheme.buttonDisabled;
      };

      lv_color_t getSuccessColor() const {
        return settings.colorScheme.success;
      };

      lv_color_t getPauseColor() const {
        return settings.colorScheme.pause;
      };

      lv_color_t getStopColor() const {
        return settings.colorScheme.stop;
      };

      lv_color_t getTextDefaultColor() const {
        return settings.colorScheme.textDefault;
      };

      void SetAppMenu(uint8_t menu) {
        appMenu = menu;
      };

      uint8_t GetAppMenu() const {
        return appMenu;
      };

      void SetSettingsMenu(uint8_t menu) {
        settingsMenu = menu;
      };
      uint8_t GetSettingsMenu() const {
        return settingsMenu;
      };

      void SetClockType(ClockType clocktype) {
        if (clocktype != settings.clockType) {
          settingsChanged = true;
        }
        settings.clockType = clocktype;
      };
      ClockType GetClockType() const {
        return settings.clockType;
      };

      void SetNotificationStatus(Notification status) {
        if (status != settings.notificationStatus) {
          settingsChanged = true;
        }
        settings.notificationStatus = status;
      };
      Notification GetNotificationStatus() const {
        return settings.notificationStatus;
      };

      void SetScreenTimeOut(uint32_t timeout) {
        if (timeout != settings.screenTimeOut) {
          settingsChanged = true;
        }
        settings.screenTimeOut = timeout;
      };

      uint32_t GetScreenTimeOut() const {
        return settings.screenTimeOut;
      };

      void SetShakeThreshold(uint16_t thresh){
        if(settings.shakeWakeThreshold != thresh){
            settings.shakeWakeThreshold = thresh;
            settingsChanged = true;
        }
        
      }

      int16_t GetShakeThreshold() const{
        return settings.shakeWakeThreshold;
      }

      void setWakeUpMode(WakeUpMode wakeUp, bool enabled) {
        if (enabled != isWakeUpModeOn(wakeUp)) {
          settingsChanged = true;
        }
        settings.wakeUpMode.set(static_cast<size_t>(wakeUp), enabled);
        // Handle special behavior
        if (enabled) {
          switch (wakeUp) {
            case WakeUpMode::SingleTap:
              settings.wakeUpMode.set(static_cast<size_t>(WakeUpMode::DoubleTap), false);
              break;
            case WakeUpMode::DoubleTap:
              settings.wakeUpMode.set(static_cast<size_t>(WakeUpMode::SingleTap), false);
              break;
            default:
              break;
          }
        }
      };

      std::bitset<4> getWakeUpModes() const {
        return settings.wakeUpMode;
      }

      bool isWakeUpModeOn(const WakeUpMode mode) const {
        return getWakeUpModes()[static_cast<size_t>(mode)];
      }

      void SetBrightness(Controllers::BrightnessController::Levels level) {
        if (level != settings.brightLevel) {
          settingsChanged = true;
        }
        settings.brightLevel = level;
      };

      Controllers::BrightnessController::Levels GetBrightness() const {
        return settings.brightLevel;
      };

      void SetStepsGoal(uint32_t goal) {
        if (goal != settings.stepsGoal) {
          settingsChanged = true;
        }
        settings.stepsGoal = goal; 
      };
      
      uint32_t GetStepsGoal() const {
        return settings.stepsGoal;
      };

     void SetBleRadioEnabled(bool enabled) {
       bleRadioEnabled = enabled;
     };

     bool GetBleRadioEnabled() const {
       return bleRadioEnabled;
     };

    private:
      Pinetime::Controllers::FS& fs;

      static constexpr uint32_t settingsVersion = 0x0004;
      struct SettingsData {
        uint32_t version = settingsVersion;
        uint32_t stepsGoal = 10000;
        uint32_t screenTimeOut = 15000;

        ClockType clockType = ClockType::H24;
        Notification notificationStatus = Notification::ON;

        uint8_t clockFace = 0;
        ChimesOption chimesOption = ChimesOption::None;

        PineTimeStyle PTS;

        ColorScheme colorScheme;

        std::bitset<4> wakeUpMode {0};
        uint16_t shakeWakeThreshold = 150;
        Controllers::BrightnessController::Levels brightLevel = Controllers::BrightnessController::Levels::Medium;
      };

      SettingsData settings;
      bool settingsChanged = false;

      uint8_t appMenu = 0;
      uint8_t settingsMenu = 0;
      /* airplaneMode is intentionally not saved with the other watch settings and initialized
       * to off (false) on every boot because we always want ble to be enabled on startup
       */
      bool bleRadioEnabled = true;

      void LoadSettingsFromFile();
      void SaveSettingsToFile();
    };
  }
}
