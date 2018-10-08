#include QMK_KEYBOARD_H
#include "led.h"

#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

#define _______ KC_TRNS

#define I3_LEFT  LGUI(KC_LEFT)
#define I3_RIGHT LGUI(KC_RIGHT)
#define I3_UP    LGUI(KC_UP)
#define I3_DOWN  LGUI(KC_DOWN)

enum custom_keycodes {
    TMUX_0 = SAFE_RANGE,
    TMUX_1,
    TMUX_2,
    TMUX_3,
    TMUX_4,
    TMUX_5,
    TMUX_6,
    TMUX_7,
    TMUX_8,
    TMUX_9,
    TMUX_NEW,
    TMUX_CLOSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-------------------.
   * |Esc |TAB | FN | BS |
   * |----|----|----|----|
   * | NL | /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----| +  |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * |   0     | .  |    |
   * `-------------------'
   */

[_BL] = LAYOUT_ortho_6x4(
  _______,    _______, MO(_FL), I3_RIGHT, \
  TMUX_CLOSE, _______, I3_UP,   I3_DOWN,  \
  TMUX_NEW,   _______, _______, I3_LEFT,  \
  _______,    TMUX_9,  TMUX_6,  TMUX_3,   \
  TMUX_0,     TMUX_8,  TMUX_5,  TMUX_2,   \
  KC_ESC,     TMUX_7,  TMUX_4,  TMUX_1),

  /* Keymap _FL: Function Layer
   * ,-------------------.
   * |RGBT|TAB | FN | BS |
   * |----|----|----|----|
   * |RGBM|RGBP|BTOG| -  |
   * |----|----|----|----|
   * |HUD |HUI |BON |    |
   * |----|----|----| +  |
   * |SAD |SAI |BOFF|    |
   * |----|----|----|----|
   * |VAD |VAS | 3  |    |
   * |----|----|----| En |
   * |   0     |RST |    |
   * `-------------------'
   */
[_FL] = LAYOUT_numpad_6x4(
  RGB_TOG,  KC_TAB,   KC_TRNS,   KC_BSPC, \
  RGB_MOD,  RGB_M_P,  BL_TOGG,   KC_PMNS, \
  RGB_HUD,  RGB_HUI,  BL_ON,              \
  RGB_SAD,  RGB_SAI,  BL_OFF,    KC_PPLS, \
  RGB_VAD,  RGB_VAI,  KC_P3,              \
  KC_P0,              RESET,     KC_PENT),
};


const uint16_t PROGMEM fn_actions[] = {
    [0] = MO(_FL),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case BL_TOGG:
    if (record->event.pressed) {
      cospad_bl_led_togg();
    }
    return false;
  case BL_ON:
    if (record->event.pressed) {
      cospad_bl_led_on();
    }
    return false;
  case BL_OFF:
    if(record->event.pressed) {
      cospad_bl_led_off();
    }
    return false;

    // tmux macros
  case TMUX_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"0");
    }
    return false;
  case TMUX_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"1");
    }
    return false;
  case TMUX_2:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"2");
    }
    return false;
  case TMUX_3:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"3");
    }
    return false;
  case TMUX_4:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"4");
    }
    return false;
  case TMUX_5:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"5");
    }
    return false;
  case TMUX_6:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"6");
    }
    return false;
  case TMUX_7:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"7");
    }
    return false;
  case TMUX_8:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"8");
    }
    return false;
  case TMUX_9:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"9");
    }
    return false;
  case TMUX_NEW:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"c");
    }
    return false;
  case TMUX_CLOSE:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTRL("b")"&y");
    }
    return false;
    
  default:
    return true;
  }
}
