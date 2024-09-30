/* Copyright 2020 gtips
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

enum layer_names {
  _WORKMAN,
  _WORKMAN_WIN,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ARROWS,
  _SYMBOLS,
  _GAMING
};

enum custom_keycodes {
  WORKMAN = SAFE_RANGE,
  GAMING,
  TO_MAC,
  TO_WIN,
  OS_CTL,
  OS_GUI,
  OS_ALT,
  OS_CUT,
  OS_CPY,
  OS_PST,
  OS_UNDO,
  OS_REDO,
  OS_NTAB,
  OS_PTAB,
  OS_DSKL,
  OS_DSKR,
  OS_DSKU,
  OS_EXIT,
  ALT_TAB
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define SFT_CAPS LSFT_T(KC_CAPS_LOCK)
#define MC_ENTER MT(MOD_LCTL, KC_ENT)
#define LT_TAB LT(_ARROWS, KC_TAB)
#define LT_QUOT LT(_SYMBOLS, KC_QUOT)

// os vars
bool is_mac = true;


// super alt tab vars
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// helper functions to process a press differently depending on the os flag
void register_os_key(uint16_t mac_keycode, uint16_t win_keycode){
    if (is_mac){
        register_code16(mac_keycode);
    } else {
        register_code16(win_keycode);
    }
}

void unregister_os_key(uint16_t mac_keycode, uint16_t win_keycode){
    if (is_mac){
        unregister_code16(mac_keycode);
    } else {
        unregister_code16(win_keycode);
    }
}

void process_os_key(bool is_pressed, uint16_t mac_keycode, uint16_t win_keycode){
    if (is_pressed) {
        register_os_key(mac_keycode, win_keycode);
    } else {
        unregister_os_key(mac_keycode, win_keycode);
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WORKMAN] = LAYOUT_reviung41(
    KC_ESC,  KC_Q,      KC_D,    KC_R,      KC_W,     KC_B,               KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN,  KC_BSPC,
    LT_TAB,  KC_A,      KC_S,    KC_H,      KC_T,     KC_G,               KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,     LT_QUOT,
    SFT_CAPS, KC_Z,     KC_X,    KC_M,      KC_C,     KC_V,               KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH,  MC_ENTER ,
                                            OS_GUI,   LOWER,   KC_SPC,    RAISE,   KC_MEH
),

  [_LOWER] = LAYOUT_reviung41(
    OS_EXIT, _______, _______, ALT_TAB, _______, _______,                              _______, OS_PTAB,   OS_DSKU,   OS_NTAB,     _______, _______,
    _______, OS_REDO, OS_UNDO, OS_PST,  OS_CPY,  OS_CUT,                               _______, OS_DSKL,   C(KC_DOWN),OS_DSKR, _______, _______,
    _______, _______, OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LGUI), _______,            _______, OSM(MOD_LGUI), OSM(MOD_LCTL), OSM(MOD_LALT),_______, _______,
                                                            _______, _______, KC_F1,    _______, _______
),

  [_RAISE] = LAYOUT_reviung41(
    _______, S(KC_MINS),KC_MINS,S(KC_EQL),KC_0,    _______,          _______, KC_1,    S(KC_8), KC_SLSH, KC_BSLS, KC_DEL,
    _______, KC_1,      KC_2,   KC_3,     KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, _______, _______, _______,   KC_5,    _______,          _______, KC_6,    _______, _______, _______, _______,
                                          _______, _______, KC_EQL,  _______, _______
),

  [_ADJUST] = LAYOUT_reviung41(
    TO_WIN,  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, GAMING,
    TO_MAC,  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______, _______, _______
),

  [_ARROWS] = LAYOUT_reviung41(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,          KC_F12,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______,
                                        _______, _______, OS_ALT, _______, _______
),

  [_SYMBOLS] = LAYOUT_reviung41(
    KC_GRV,  S(KC_1), S(KC_2),   S(KC_3),   S(KC_4), _______,         _______, S(KC_5), S(KC_7),    S(KC_BSLS),S(KC_6), XXXXXXX,
    _______, _______, S(KC_COMM),S(KC_LBRC),S(KC_9), KC_LBRC,         KC_RBRC, S(KC_0), S(KC_RBRC), S(KC_DOT),_______,    _______,
    _______, _______, _______,   _______,   KC_LBRC, _______,         _______, KC_RBRC, _______,    _______,  _______,    _______,
                                            _______, _______, KC_EQL, _______, _______
),
  [_GAMING] = LAYOUT_reviung41(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    WORKMAN,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT ,
                                        KC_LCTL, KC_BTN2, KC_SPC,  XXXXXXX, XXXXXXX
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GAMING:
            if (record->event.pressed) {
                autoshift_disable();
                layer_on(_GAMING);
            }
            return false;
            break;

        case WORKMAN:
            if (record->event.pressed) {
                autoshift_enable();
                layer_off(_GAMING);
            }
            return false;
            break;

        case TO_MAC:
            is_mac = true;
            return false;

        case TO_WIN:
            is_mac = false;
            return false;

        case OS_CTL:
            process_os_key(record->event.pressed, KC_LCTL, KC_LGUI);
            return false;

        case OS_GUI:
            process_os_key(record->event.pressed, KC_LGUI, KC_LCTL);
            return false;

        case OS_ALT:
            process_os_key(record->event.pressed, KC_LALT, KC_LCTL);
            return false;

        case OS_CUT:
            process_os_key(record->event.pressed, G(KC_X), C(KC_X));
            return false;

        case OS_CPY:
            process_os_key(record->event.pressed, G(KC_C), C(KC_C));
            return false;

        case OS_PST:
            process_os_key(record->event.pressed, G(KC_V), C(KC_V));
            return false;

        case OS_UNDO:
            process_os_key(record->event.pressed, G(KC_Z), C(KC_Z));
            return false;

        case OS_REDO:
            process_os_key(record->event.pressed, SGUI(KC_Z), C(KC_Y));
            return false;

        case OS_PTAB:
            process_os_key(record->event.pressed, SGUI(KC_LBRC), C(KC_PGUP));
            return false;

        case OS_NTAB:
            process_os_key(record->event.pressed, SGUI(KC_RBRC), C(KC_PGDN));
            return false;

        case OS_DSKL:
            process_os_key(record->event.pressed, C(KC_LEFT), G(C(KC_LEFT)));
            return false;

        case OS_DSKR:
            process_os_key(record->event.pressed, C(KC_RIGHT), G(C(KC_RIGHT)));
            return false;

        case OS_DSKU:
            process_os_key(record->event.pressed, C(KC_UP), G(KC_TAB));
            return false;

        case OS_EXIT:
            process_os_key(record->event.pressed, G(KC_Q), A(KC_F4));
            return false;

        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_os_key(KC_LGUI, KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}


void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_os_key(KC_LGUI, KC_LALT);
      is_alt_tab_active = false;
    }
  }
}


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
