// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// encoder
#define EN_VOL ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
#define EN_ZOOM ENCODER_CCW_CW(LGUI(KC_MINUS), LSG(KC_EQUAL))

// audio / media
#define AM_MUTE KC_MUTE

// layer toggle
#define OSPASS OSL(_PASSWORDS)

// vs-code
bool is_dark = true;

// macros
enum my_keycodes {
    PW_WRK1 = SAFE_RANGE,
    PW_WRK2,
    VS_DARK,
    VS_PRY
};

// terminal
#define TM_STOP C(KC_C)
#define TM_EXIT C(KC_D)

enum layer_names {
  _VSCODE,
  _PASSWORDS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_VSCODE] = LAYOUT(
      OSPASS,             AM_MUTE,
      TM_EXIT,  XXXXXXX,  XXXXXXX,
      TM_STOP,  VS_PRY,   VS_DARK
      ),
    [_PASSWORDS] = LAYOUT(
      XXXXXXX,            _______,
      PW_WRK1,  PW_WRK2,  XXXXXXX,
      XXXXXXX,  XXXXXXX,  XXXXXXX
      )
};


/*Encoder Mapping*/
//-----------------------(ENC1)---------------------------------(ENC2)-----------------
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_VSCODE] =  { EN_ZOOM, EN_VOL  },
  [_PASSWORDS] =  { EN_ZOOM, EN_VOL  }
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // vscode
    case VS_DARK:
      if (record->event.pressed) {
        if (is_dark) {
          is_dark = false;
          SEND_STRING(SS_LGUI("kt") "atoh\n");
        } else {
          is_dark = true;
          SEND_STRING(SS_LGUI("kt") "ato\n");
        }
      }
      return false;
    case VS_PRY:
      if (record->event.pressed) {
        SEND_STRING("\nrequire \"pry-nav\"; binding.pry");
      }
      return false;
    // passwords
    case PW_WRK1:
      if (record->event.pressed) {
        SEND_STRING("---"); // one password
      }
      return false;
    case PW_WRK2:
      if (record->event.pressed) {
        send_string_with_delay("---", 50); // login
      }
      return false;
    default:
      return true;
  }
}

// lighting
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _PASSWORDS:
        rgblight_setrgb(RGB_RED);
        break;
    default:
        rgblight_setrgb(RGB_OFF);
        break;
    }
  return state;
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // For RGB underglow
  rgblight_setrgb(RGB_OFF);
}

