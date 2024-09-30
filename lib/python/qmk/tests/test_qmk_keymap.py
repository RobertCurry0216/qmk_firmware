import qmk.keymap


def test_generate_c_pytest_basic():
    keymap_json = {
        'keyboard': 'handwired/pytest/basic',
        'layout': 'LAYOUT',
        'layers': [['KC_A']],
        'macros': None,
    }
    templ = qmk.keymap.generate_c(keymap_json)
    assert templ == """#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif


/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_A)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)


"""


def test_generate_json_pytest_basic():
    templ = qmk.keymap.generate_json('default', 'handwired/pytest/basic', 'LAYOUT', [['KC_A']])
    assert templ == {"keyboard": "handwired/pytest/basic", "keymap": "default", "layout": "LAYOUT", "layers": [["KC_A"]]}


def test_parse_keymap_c():
    parsed_keymap_c = qmk.keymap.parse_keymap_c('keyboards/handwired/pytest/basic/keymaps/default/keymap.c')
    assert parsed_keymap_c == {'layers': [{'name': '0', 'layout': 'LAYOUT_ortho_1x1', 'keycodes': ['KC_A']}]}


# FIXME(skullydazed): Add a test for qmk.keymap.write that mocks up an FD.
