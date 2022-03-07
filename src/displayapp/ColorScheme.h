#pragma once

#include <lvgl/src/lv_misc/lv_color.h>

class ColorScheme {
    private:
        lv_color_t background;
        lv_color_t accentPrimary;
        lv_color_t accentSecondary;
        lv_color_t buttonDefault;
        lv_color_t buttonDisabled;
        lv_color_t success;
        lv_color_t pause;
        lv_color_t stop;
        lv_color_t textDefault;

    public:
        ColorScheme();
        ColorScheme(lv_color_t background, lv_color_t accentPrimary, lv_color_t accentSecondary, lv_color_t buttonDefault, lv_color_t buttonDisabled, 
                    lv_color_t success, lv_color_t pause, lv_color_t stop, lv_color_t textDefault);
        lv_color_t getBackgroundColor();
        lv_color_t getAccentPrimaryColor();
        lv_color_t getAccentSecondaryColor();
        lv_color_t getButtonDefaultColor();
        lv_color_t getButtonDisabledColor();
        lv_color_t getSuccessColor();
        lv_color_t getPauseColor();
        lv_color_t getStopColor();
        lv_color_t getTextDefaultColor();

};