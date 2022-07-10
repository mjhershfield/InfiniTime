#pragma once

#include <cstdint>
#include <lvgl/lvgl.h>
#include <array>
#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"

namespace Pinetime {

  namespace Applications {
    namespace Screens {

      class SettingTheme : public Screen{
        public:
          SettingTheme(DisplayApp* app, Pinetime::Controllers::Settings &settingsController);
          ~SettingTheme() override;

          void UpdateSelected(lv_obj_t *object, lv_event_t event);
         
        private:          
          Controllers::Settings& settingsController;

          Controllers::Settings::ColorScheme themes[3];

          // TODO: transition to using arrays instead of individually declared objects
          lv_obj_t* themeBtns[3];
          lv_obj_t* themeLabels[3];
          lv_obj_t* editBtns[3];
          lv_obj_t* editLabels[3];

          lv_obj_t * btnTheme1;
          lv_obj_t * btnTheme2;
          lv_obj_t * btnTheme3;
          lv_obj_t * btnEditTheme1;
          lv_obj_t * btnEditTheme2;
          lv_obj_t * btnEditTheme3;
          lv_obj_t * labelTheme1;
          lv_obj_t * labelTheme2;
          lv_obj_t * labelTheme3;
          lv_obj_t * labelIcon1;
          lv_obj_t * labelIcon2;
          lv_obj_t * labelIcon3;
          lv_obj_t * backgroundLabel;
      };
    }
  }
}