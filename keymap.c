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
#define BROWSER 2
#define WM 3

#define _______ KC_TRNS

#define I3_LEFT  LGUI(KC_LEFT)
#define I3_RIGHT LGUI(KC_RIGHT)
#define I3_UP    LGUI(KC_UP)
#define I3_DOWN  LGUI(KC_DOWN)
#define I3_0 LGUI(KC_0)
#define I3_1 LGUI(KC_1)
#define I3_2 LGUI(KC_2)
#define I3_3 LGUI(KC_3)
#define I3_4 LGUI(KC_4)
#define I3_5 LGUI(KC_5)
#define I3_6 LGUI(KC_6)
#define I3_7 LGUI(KC_7)
#define I3_8 LGUI(KC_8)
#define I3_9 LGUI(KC_9)

#define BRW_0 LALT(KC_0)
#define BRW_1 LALT(KC_1)
#define BRW_2 LALT(KC_2)
#define BRW_3 LALT(KC_3)
#define BRW_4 LALT(KC_4)
#define BRW_5 LALT(KC_5)
#define BRW_6 LALT(KC_6)
#define BRW_7 LALT(KC_7)
#define BRW_8 LALT(KC_8)
#define BRW_9 LALT(KC_9)
#define BRW_OPEN LCTL(KC_T)
#define BRW_CLOSE LCTL(KC_W)
#define BRW_REFRESH LCTL(KC_R)

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
  _______,    _______, MO(_FL),     I3_RIGHT, \
  TMUX_CLOSE, _______, I3_UP,       I3_DOWN,  \
  TMUX_NEW,   TG(WM),  TG(BROWSER), I3_LEFT,        \
  _______,    TMUX_9,  TMUX_6,      TMUX_3,   \
  TMUX_0,     TMUX_8,  TMUX_5,      TMUX_2,   \
  KC_ESC,     TMUX_7,  TMUX_4,      TMUX_1),

[BROWSER] = LAYOUT_ortho_6x4(
  BRW_REFRESH, _______, _______, _______,\
  BRW_CLOSE,   _______, _______, _______,\
  BRW_OPEN,    _______, _______, _______,\
  _______,     BRW_9,   BRW_6,   BRW_3,  \
  _______,     BRW_8,   BRW_5,   BRW_2,  \
  KC_EXEC,     BRW_7,   BRW_4,   BRW_1),

[WM] = LAYOUT_ortho_6x4(
  _______,     _______, _______, _______,\
  _______,     _______, _______, _______,\
  _______,     _______, _______, _______,\
  _______,     I3_9,    I3_6,    I3_3,   \
  _______,     I3_8,    I3_5,    I3_2,   \
  KC_EXEC,     I3_7,    I3_4,    I3_1),

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
