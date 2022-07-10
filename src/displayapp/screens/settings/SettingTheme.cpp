#include "displayapp/screens/settings/SettingTheme.h"
#include <lvgl/lvgl.h>
#include <string>
#include "displayapp/Colors.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Symbols.h"
#include "displayapp/lv_pinetime_theme.h"

using namespace Pinetime::Applications::Screens;

namespace {
  static void event_handler(lv_obj_t* obj, lv_event_t event) {
    SettingTheme* screen = static_cast<SettingTheme*>(obj->user_data);
    screen->UpdateSelected(obj, event);
  }
}

SettingTheme::SettingTheme(Pinetime::Applications::DisplayApp* app, Pinetime::Controllers::Settings& settingsController)
  : Screen(app), settingsController {settingsController} {

  for (int i = 0; i < 3; i++) {
    themes[i] = settingsController.getTheme(i);

    // make three buttons and labels
    themeBtns[i] = lv_btn_create(lv_scr_act(), nullptr);
    lv_obj_set_size(themeBtns[i], 160, 60);
    lv_obj_align(themeBtns[i], lv_scr_act(), LV_ALIGN_CENTER, -40, (80 * (i - 1)));
    lv_obj_set_style_local_bg_color(themeBtns[i], LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Convert(themes[i].primary, themes[i].primaryTint));

    themeLabels[i] = lv_label_create(themeBtns[i], nullptr);
    lv_label_set_text_static(themeLabels[i], "THEME");
    lv_label_set_align(themeLabels[i], LV_LABEL_ALIGN_CENTER);

    editBtns[i] = lv_btn_create(lv_scr_act(), nullptr);
    lv_obj_set_size(editBtns[i], 60, 60);
    lv_obj_align(editBtns[i], lv_scr_act(), LV_ALIGN_CENTER, 90, (80 * (i - 1)));
    lv_obj_set_style_local_bg_color(editBtns[i], LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Convert(themes[i].surface, themes[i].surfaceTint));

    editLabels[i] = lv_label_create(editBtns[i], nullptr);
    lv_label_set_text_static(editLabels[i], Symbols::paintbrush);
  }
  
  // btnTheme1 = lv_btn_create(lv_scr_act(), nullptr);
  // lv_obj_set_size(btnTheme1, 160, 60);
  // lv_obj_align(btnTheme1, lv_scr_act(), LV_ALIGN_CENTER, -40, -80);
  // lv_obj_set_style_local_bg_color(btnTheme1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);

  // btnEditTheme1 = lv_btn_create(lv_scr_act(), nullptr);
  // lv_obj_set_size(btnEditTheme1, 60, 60);
  // lv_obj_align(btnEditTheme1, lv_scr_act(), LV_ALIGN_CENTER, 90, -80);
  // lv_obj_set_style_local_bg_color(btnEditTheme1, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Convert(themes[0].surface, themes[0].surfaceTint));

  // btnTheme2 = lv_btn_create(lv_scr_act(), nullptr);
  // lv_obj_set_size(btnTheme2, 160, 60);
  // lv_obj_align(btnTheme2, lv_scr_act(), LV_ALIGN_CENTER, -40, 0);
  // lv_obj_set_style_local_bg_color(btnTheme2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GREEN);

  // btnEditTheme2 = lv_btn_create(lv_scr_act(), nullptr);
  // lv_obj_set_size(btnEditTheme2, 60, 60);
  // lv_obj_align(btnEditTheme2, lv_scr_act(), LV_ALIGN_CENTER, 90, 0);
  // lv_obj_set_style_local_bg_color(btnEditTheme2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GREEN);

  // btnTheme3 = lv_btn_create(lv_scr_act(), nullptr);
  // lv_obj_set_size(btnTheme3, 160, 60);
  // lv_obj_align(btnTheme3, lv_scr_act(), LV_ALIGN_CENTER, -40, 80);
  // lv_obj_set_style_local_bg_color(btnTheme3, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);

  // btnEditTheme3 = lv_btn_create(lv_scr_act(), nullptr);
  // lv_obj_set_size(btnEditTheme3, 60, 60);
  // lv_obj_align(btnEditTheme3, lv_scr_act(), LV_ALIGN_CENTER, 90, 80);
  // lv_obj_set_style_local_bg_color(btnEditTheme3, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);

  backgroundLabel = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_click(backgroundLabel, true);
  lv_label_set_long_mode(backgroundLabel, LV_LABEL_LONG_CROP);
  lv_obj_set_size(backgroundLabel, 240, 240);
  lv_obj_set_pos(backgroundLabel, 0, 0);
  lv_label_set_text(backgroundLabel, "");

  // labelTheme1 = lv_label_create(btnTheme1, nullptr);
  // lv_label_set_text_static(labelTheme1, "Theme 1");
  // lv_label_set_align(labelTheme1, LV_LABEL_ALIGN_CENTER);

  // labelTheme2 = lv_label_create(btnTheme2, nullptr);
  // lv_label_set_text_static(labelTheme2, "Theme 2");
  // lv_label_set_align(labelTheme2, LV_LABEL_ALIGN_CENTER);

  // labelTheme3 = lv_label_create(btnTheme3, nullptr);
  // lv_label_set_text_static(labelTheme3, "Theme 3");
  // lv_label_set_align(labelTheme3, LV_LABEL_ALIGN_CENTER);

  // labelIcon1 = lv_label_create(btnEditTheme1, nullptr);
  // lv_label_set_text_static(labelIcon1, Symbols::paintbrush);

  // labelIcon2 = lv_label_create(btnEditTheme2, nullptr);
  // lv_label_set_text_static(labelIcon2, Symbols::paintbrush);

  // labelIcon3 = lv_label_create(btnEditTheme3, nullptr);
  // lv_label_set_text_static(labelIcon3, Symbols::paintbrush);
}

void SettingTheme::UpdateSelected(lv_obj_t *object, lv_event_t event) {
  if (event == LV_EVENT_CLICKED) {
    if (object == editBtns[0]) {
      this->app->StartApp(Applications::Apps::SettingColorPicker, DisplayApp::FullRefreshDirections::Up);
    }
  }
}

SettingTheme::~SettingTheme() {
  lv_obj_clean(lv_scr_act());
  settingsController.SaveSettings();
}
