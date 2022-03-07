#include "ColorScheme.h"

// Default Values are based on PineTime Theme from Infinitime 1.8.0
ColorScheme::ColorScheme()
  : background{lv_color_hex(0x000000)}, 
    accentPrimary{lv_color_hex(0xFFA500)}, 
    accentSecondary{lv_color_hex(0x00FFE7)}, 
    buttonDefault{lv_color_hex(0x111111)}, 
    buttonDisabled{lv_color_hex(0xAEAEAE)}, 
    success{lv_color_hex(0x008000)}, 
    pause{lv_color_hex(0xFFFF00)}, 
    stop{lv_color_hex(0xFF0000)}, 
    textDefault{lv_color_hex(0xFFFFFF)} {};

ColorScheme::ColorScheme(lv_color_t background, 
                         lv_color_t accentPrimary, 
                         lv_color_t accentSecondary, 
                         lv_color_t buttonDefault, 
                         lv_color_t buttonDisabled, 
                         lv_color_t success, 
                         lv_color_t pause, 
                         lv_color_t stop, 
                         lv_color_t textDefault)
  : background{background}, 
    accentPrimary{accentPrimary}, 
    accentSecondary{accentSecondary}, 
    buttonDefault{buttonDefault}, 
    buttonDisabled{buttonDisabled},
    success{success}, 
    pause{pause}, 
    stop{stop}, 
    textDefault{textDefault} {};

lv_color_t ColorScheme::getBackgroundColor() {
    return background;
}

lv_color_t ColorScheme::getAccentPrimaryColor() {
    return accentPrimary;
}

lv_color_t ColorScheme::getAccentSecondaryColor() {
    return accentSecondary;
}

lv_color_t ColorScheme::getButtonDefaultColor() {
    return buttonDefault;
}

lv_color_t ColorScheme::getButtonDisabledColor() {
    return buttonDisabled;
}

lv_color_t ColorScheme::getSuccessColor() {
    return success;
}

lv_color_t ColorScheme::getPauseColor() {
    return pause;
}

lv_color_t ColorScheme::getStopColor() {
    return stop;
}

lv_color_t ColorScheme::getTextDefaultColor() {
    return textDefault;
}

