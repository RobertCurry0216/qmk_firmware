/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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
#include <stdlib.h>
#include QMK_KEYBOARD_H

// mac keycodes
#define KC_MAC_COPY G(KC_C)
#define KC_MAC_PASTE G(KC_V)
#define KC_MAC_UNDO G(KC_Z)
#define KC_MAC_REDO SGUI(KC_Z)

// windows keycodes
#define KC_WIN_COPY C(KC_C)
#define KC_WIN_PASTE C(KC_V)
#define KC_WIN_UNDO C(KC_Z)
#define KC_WIN_REDO C(KC_Y)
#define KC_WIN_PSCR SGUI(KC_S)

// safe range starts at `PLOOPY_SAFE_RANGE` instead.
enum {
    KC_GESTURE=PLOOPY_SAFE_RANGE,
    KC_WIN,
    KC_MAC
};

enum ploopy_layers {
    MAIN,
    CONFIG
};

// swipe gesture vars
bool is_swipe_gesture = false;
int16_t swipe_x = 0;
int16_t swipe_y = 0;
const int16_t SWIPE_THRESHOLD = 10;

// os vars
bool is_mac = true;

// acceleration vars
float acc_a = 0.85;
float acc_b = 0.7;

int16_t acceleration(int16_t v) {
    if (v == 0){
        return v;
    }
    int16_t s = v / abs(v);
    return (int16_t)(v*acc_a + v*v*s*acc_b);
}

void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
    if (is_swipe_gesture) {
        swipe_x += x;
        swipe_y += y;
    } else {
        mouse_report->x = acceleration(x);
        mouse_report->y = acceleration(y);
    }
}

void process_swipe_gesture(int16_t x, int16_t y) {
    if (abs(x) < SWIPE_THRESHOLD && abs(y) < SWIPE_THRESHOLD) {
        if (is_mac){
            register_code(KC_LCTL);
            tap_code16(SGUI(KC_4));
            unregister_code(KC_LCTL);
        } else {
            tap_code16(KC_WIN_PSCR);
        }
        return;
    }

    if (abs(x) > abs(y)){
        if (x > 0) { // swipe right
            if (is_mac){
                tap_code16(KC_MAC_PASTE);
            } else {
                tap_code16(KC_WIN_PASTE);
            }
        } else { // swipe left
            if (is_mac) {
                tap_code16(KC_MAC_COPY);
            } else {
                tap_code16(KC_WIN_COPY);
            }
        }
    } else {
        if (y > 0){ // swipe back
            if (is_mac) {
                tap_code16(KC_MAC_REDO);
            } else {
                tap_code16(KC_WIN_REDO);
            }
        } else { // swipe forward
            if (is_mac) {
                tap_code16(KC_MAC_UNDO);
            } else {
                tap_code16(KC_WIN_UNDO);
            }
        }
    }
}

//turn off mouse wheel
void process_wheel_user(report_mouse_t* mouse_report, int16_t h, int16_t v) {}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAIN] = LAYOUT( /* Base */
        KC_BTN1, KC_BTN3, KC_GESTURE, KC_BTN2, DRAG_SCROLL
    ),
    [CONFIG] = LAYOUT( /* config */
        _______, _______, _______, KC_WIN, KC_MAC
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_GESTURE:
            if (record->event.pressed) {
                layer_on(CONFIG);
                is_swipe_gesture = true;
            } else {
                layer_off(CONFIG);
                process_swipe_gesture(swipe_x, swipe_y);
                swipe_x = 0;
                swipe_y = 0;
                is_swipe_gesture = false;
            }
            return false;
        case KC_WIN:
            is_mac = false;
            return false;
        case KC_MAC:
            is_mac = true;
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}
