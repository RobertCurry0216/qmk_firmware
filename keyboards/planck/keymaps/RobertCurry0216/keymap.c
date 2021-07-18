/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H


enum planck_layers {
  _WORKMAN,
  _WORKMAN_WIN,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ARROWS,
  _SYMBOLS,
  _QWERTY
};

enum planck_keycodes {
  WORKMAN = SAFE_RANGE,
  QWERTY,
  TOWIN,
  TOMAC
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE) 
#define SFT_CAPS LSFT_T(KC_CAPSLOCK)
#define LT_TAB LT(_ARROWS, KC_TAB)
#define LT_QUOT LT(_SYMBOLS, KC_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Worman
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  |   K  |   L  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |Hyper | GUI  |Lower |    Space    |Raise | Meh  |BLdwn | BLup |BLcyc |
 * `-----------------------------------------------------------------------------------'
 */
[_WORKMAN] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN,    KC_BSPC,
    LT_TAB,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I, LT_QUOT,
    SFT_CAPS, KC_Z,   KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, KC_LALT, KC_HYPR, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_MEH, RGB_HUI, RGB_VAI, RGB_TOG
),


/* Worman
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  |   K  |   L  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |Hyper | GUI  |Lower |    Space    |Raise | Meh  |BLdwn | BLup |BLcyc |
 * `-----------------------------------------------------------------------------------'
 */
[_WORKMAN_WIN] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN,    KC_BSPC,
    LT_TAB,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I, LT_QUOT,
    SFT_CAPS, KC_Z,   KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LGUI, KC_LALT, KC_HYPR, KC_LCTL, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_MEH, RGB_HUI, RGB_VAI, RGB_TOG
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |   -  |   +  |   0  |      |      |   1  |   *  |   /  |   \  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  6   |  7   |  8   |  9   |      |      |   2  |   3  |   4  |   5  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      =      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, _______, KC_MINS, S(KC_EQL),KC_0,   _______, _______, KC_1,    S(KC_8), KC_SLSH, KC_BSLS, KC_DEL,
    _______, KC_6,    KC_7,    KC_8,    KC_9,    _______, _______, KC_2,    KC_3,    KC_4,    KC_5,    _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_EQL,  KC_EQL,  _______, _______, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      | tab L| mis c| tab R|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | scn L| scn D| scn R|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Cmd pal  |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______,SGUI(KC_LBRC),C(KC_UP),  SGUI(KC_RBRC), _______, _______,
    _______, _______, _______, _______, _______, _______, _______,C(KC_LEFT),   C(KC_DOWN),C(KC_RIGHT),   _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,      _______,       _______, _______,
    _______, _______, _______, _______, _______, KC_F1,   KC_F1,   _______,  _______,      _______,       _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    TOWIN,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, WORKMAN,
    TOMAC,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Arrows
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | Home |  Up  |  End |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | Left | Down | Right|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | w l  | w dn | w up | w r  |
 * `-----------------------------------------------------------------------------------'
 */
[_ARROWS] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_HOME, KC_UP,   KC_END,  _______, _______,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_LALT, KC_LALT, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R
),

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   !  |   @  |   #  |   $  |      |      |   %  |   ^  |   &  |   \  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   <  |   {  |   (  |   [  |   ]  |   )  |   }  |   >  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      =      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = LAYOUT_planck_grid(
    KC_GRV,  S(KC_1), S(KC_2),   S(KC_3),   S(KC_4), _______, _______, S(KC_5), S(KC_6),    S(KC_7),  S(KC_BSLS), _______,
    _______, _______, S(KC_COMM),S(KC_LBRC),S(KC_9), KC_LBRC, KC_RBRC, S(KC_0), S(KC_RBRC), S(KC_DOT),_______,    _______,
    _______, _______, _______,   _______,   _______, _______, _______, _______, _______,    _______,  _______,    _______,
    _______, _______, _______,   _______,   _______, KC_EQL,  KC_EQL,  _______, _______,    _______,  _______,    _______
),
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    _______,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______ ,
    XXXXXXX, _______, _______, _______, _______,   _______,  _______,  _______,   KC_LEFT, KC_UP, KC_DOWN, KC_RIGHT
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                autoshift_disable();
                layer_on(_QWERTY);
            }
            return false;
            break;
        case WORKMAN:
            if (record->event.pressed) {
                autoshift_enable();
                layer_off(_QWERTY);
            }
            return false;
            break;
        case TOWIN:
            DF(_WORKMAN_WIN);
            return false;
            break;
        case TOMAC:
            DF(_WORKMAN);
            return false;
            break;

    }
    return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}