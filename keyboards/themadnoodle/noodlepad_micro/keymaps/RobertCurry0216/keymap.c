// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// encoder
#define EN_VOL ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
#define EN_ZOOM ENCODER_CCW_CW(LGUI(KC_MINUS), LSG(KC_EQUAL))

// audio / media
#define AM_MUTE KC_MUTE

// layer toggle
#define TLAYER TG(_ARROWS)

// terminal
#define TM_STOP C(KC_C)
#define TM_EXIT C(KC_D)

enum layer_names {
  _MEDIA,
  _ARROWS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MEDIA] = LAYOUT(
        TLAYER,   AM_MUTE,
        KC_MPRV,  KC_MPLY,  KC_MNXT,
        KC_MSTP,  KC_VOLD,  KC_VOLU
    ),
    [_ARROWS] = LAYOUT(
        TLAYER,             AM_MUTE,
        KC_Z,     KC_UP,    KC_X,
        KC_LEFT,  KC_DOWN,  KC_RIGHT
    ),
};


/*Encoder Mapping*/
//-----------------------(ENC1)---------------------------------(ENC2)-----------------
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_MEDIA] =  { EN_ZOOM, EN_VOL  },
  [_ARROWS] =  { EN_ZOOM, EN_VOL  }
};
#endif

// RGB layer lighting
const rgblight_segment_t PROGMEM media_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_OFF}
);

const rgblight_segment_t PROGMEM arrows_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_BLUE}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    media_layer,
    arrows_layer
);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
    rgblight_set_layer_state(0, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, !layer_state_cmp(state, _ARROWS));
    rgblight_set_layer_state(1, layer_state_cmp(state, _ARROWS));
    return state;
}
