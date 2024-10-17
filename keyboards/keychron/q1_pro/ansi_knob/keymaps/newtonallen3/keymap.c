/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

// clang-format off
enum layers{
  MAC_BASE,         // 0
  MAC_FN,           // 1
  WIN_BASE,         // 2
  WIN_NAV,          // 3
  WIN_NUMPAD,       // 4
  WIN_DESKTOP_NAV,  // 5
  WIN_TERMINAL_NAV, // 6
  WIN_TAB_NAV,      // 7
  WIN_WINDOW_NAV,   // 8
  WIN_COLEMAK_DH,   // 9
};


// Home row mods ("GACS"). From https://precondition.github.io/home-row-mods#use-left-and-right-modifiers-but-beware-of-altgr.
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L RALT_T(KC_L)
#define HOME_SCLN LGUI_T(KC_SCLN) // LGUI is used since RGUI doesn't trigger Linux app switcher

// Caps lock == Escape if tapped; nav layer if held.
#define ESC_OR_NAV LT(WIN_NAV, KC_ESC)

// n and v: if held, enable num layer.
#define N_OR_NUM LT(WIN_NUMPAD, KC_N)
#define V_OR_NUM LT(WIN_NUMPAD, KC_V)

// e: if held, enable Ctrl+Alt nav layer.
#define E_OR_NAV LT(WIN_DESKTOP_NAV, KC_E)

// w: if held, enable Alt nav layer.
#define W_OR_NAV LT(WIN_TERMINAL_NAV, KC_W)

// r: if held, enable layer for Tab+PageUp tab navigation.
#define R_OR_NAV LT(WIN_TAB_NAV, KC_R)

// z: if held, enable layer for Alt+Tab for window switching.
// TODO: make this work. It's not currently switching layers. Need to use
// Tap Dance to achieve both layer switching and modifier addition when held.
#define Z_OR_NAV LALT_T(KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_LCMMD,MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

    // With home row mods
    //[WIN_BASE] = LAYOUT_ansi_82(
    //    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             KC_MUTE,
    //    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
    //    KC_TAB,   KC_Q,     W_OR_NAV, E_OR_NAV, R_OR_NAV, KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
    //    ESC_OR_NAV, HOME_A, HOME_S,   HOME_D,   HOME_F,   KC_G,     KC_H,     HOME_J,   HOME_K,   HOME_L,   HOME_SCLN, KC_QUOT,           KC_ENT,             KC_HOME,
    //    KC_LSFT,            KC_Z,     KC_X,     KC_C,     V_OR_NUM, KC_B,     N_OR_NUM, KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
    //    KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 TG(4),    MO(3),    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    // Basic layout, no home row mods
    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(3),    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_NAV] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  TO(9),    KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_INS,            RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PGUP,  KC_UP,    KC_PGDN,  KC_PSCR,  _______,  _______,  _______,            _______,
        _______,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  _______,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END,   _______,            _______,            KC_END,
        _______,            C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  _______,  KC_BSPC,  KC_DEL,   KC_INS,   _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                TO(2),                                  _______,  _______,  _______,  _______,  _______,  _______),

    [WIN_NUMPAD] = LAYOUT_ansi_82(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  KC_PAST,  KC_7,     KC_8,     KC_9,     KC_PPLS,  _______,  KC_LBRC,  KC_RBRC,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  KC_0,     KC_1,     KC_2,     KC_3,     KC_EQL,   KC_UNDS,  KC_LPRN,  KC_RPRN,  KC_LCBR,  KC_RCBR,  _______,            _______,            _______,
        _______,            KC_DOT,   KC_4,     KC_5,     KC_6,     KC_PMNS,  KC_BSPC,  KC_DEL,   _______,  _______,  KC_SLSH,            _______,  _______,
        _______,  _______,  _______,                                KC_SPC,                                 _______,  _______,  _______,  _______,  _______,  _______),

    // For moving between desktops. The arrow keys have Ctrl+Alt already enabled. Shift can be added if desired.
    [WIN_DESKTOP_NAV] = LAYOUT_ansi_82(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  LCA(KC_UP),XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,  XXXXXXX,  LCA(KC_LEFT),LCA(KC_DOWN),LCA(KC_RGHT),XXXXXXX,XXXXXXX,     XXXXXXX,            XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                TO(2),                                  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

    // For moving between tmux panes. The arrow keys have Alt already enabled.
    [WIN_TERMINAL_NAV] = LAYOUT_ansi_82(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  A(KC_UP), XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX,  XXXXXXX,  A(KC_LEFT),A(KC_DOWN),A(KC_RGHT),XXXXXXX,XXXXXXX,           XXXXXXX,            XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                TO(2),                                  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

    // For moving between tabs and rearranging (Ctrl+Tab, Ctrl+PageUp, etc).
    [WIN_TAB_NAV] = LAYOUT_ansi_82(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, C(S(KC_PGUP)),XXXXXXX,XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  C(S(KC_TAB)),C(S(KC_PGDN)),C(KC_TAB),XXXXXXX,XXXXXXX,       XXXXXXX,            XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                TO(2),                                  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

    // For switching between windows (Alt+Tab).
    [WIN_WINDOW_NAV] = LAYOUT_ansi_82(
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  S(KC_TAB),KC_TAB,   XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,            XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                TO(2),                                  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX),

    // Colemak DH (accessed via Fn+F3).
    [WIN_COLEMAK_DH] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_ESC,   KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_X,     KC_C,     KC_D,     KC_V,     KC_Z,     KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 TO(2),    MO(3),    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_NAV] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_NUMPAD] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_DESKTOP_NAV] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_TERMINAL_NAV] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_TAB_NAV] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_WINDOW_NAV] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_COLEMAK_DH] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

// shift backspace sends delete. (same for ctrl+shift for deleting entire
// words).
//const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
//const key_override_t **key_overrides = (const key_override_t *[]){
//    &delete_key_override,
//    NULL // Null terminate the array of overrides!
//};

// LEDs indicate current layer (solid color for each layer; base layer is unlit).
//
// Example: https://github.com/nblyumberg/qmk_firmware/blob/71620555425803c114decae3ef3136511a368b2f/keyboards/keebio/bdn9/keymaps/nblyumberg/keymap.c#L278
//
// Ideally, we'd override rgb_matrix_indicators_user() here. However, Keychron's
// code has already overridden this function to provide Bluetooth indicator
// lights.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  // Option 1: Illuminate just a few LEDs.
/*
  switch (get_highest_layer(layer_state)) {
    case WIN_NAV:
      rgb_matrix_set_color_all(0,0,0);
      rgb_matrix_set_color(6, 75, 255, 75);
      rgb_matrix_set_color(7, 75, 255, 75);
      break;
    case WIN_NUMPAD:
      rgb_matrix_set_color_all(0, 0, 0);
      rgb_matrix_set_color(6, 0, 204, 0);
      rgb_matrix_set_color(7, 0, 204, 0);
      rgb_matrix_set_color(8, 0, 204, 0);
      break;
    default:
      break;
  }
  return true;
*/

  // Option 2: Illuminate entire keyboard.
  for (uint8_t i = led_min; i < led_max; i++) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
      case 1:
        rgb_matrix_set_color(i, RGB_GREEN);
        break;
      case 2:
        rgb_matrix_set_color(i, 0, 0, 0);
        break;
      case 3:
        rgb_matrix_set_color(i, RGB_BLUE);
        break;
      case 4:
        rgb_matrix_set_color(i, RGB_YELLOW);
        break;
      // Special nav layers don't need color
      case 5:
      case 6:
      case 7:
        rgb_matrix_set_color(i, 0, 0, 0);
        break;
      case 8:
        rgb_matrix_set_color(i, RGB_RED);
        break;
      case 9:
        rgb_matrix_set_color(i, RGB_GREEN);
        break;
      default:
        break;
    }
  }
  return false;
}
