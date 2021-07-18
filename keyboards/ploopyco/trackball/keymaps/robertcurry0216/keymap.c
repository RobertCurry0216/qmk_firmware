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
#include QMK_KEYBOARD_H

#define KC_COPY LGUI(KC_C)
#define KC_PASTE LGUI(KC_V)

#define KC_WCOPY LSFT(KC_C)
#define KC_WPASTE LSFT(KC_V)

// safe range starts at `PLOOPY_SAFE_RANGE` instead.
enum {
    TD_CPY_PST,
    TD_WCPY_WPST,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CPY_PST] = ACTION_TAP_DANCE_DOUBLE(KC_COPY, KC_PASTE),
    [TD_WCPY_WPST] = ACTION_TAP_DANCE_DOUBLE(KC_WCOPY, KC_WPASTE),
};

//turn off mouse wheel
void process_wheel_user(report_mouse_t* mouse_report, int16_t h, int16_t v) {}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN1, KC_BTN3, TD(TD_CPY_PST), KC_BTN2, DRAG_SCROLL
    )
};
