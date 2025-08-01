#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

#define REPEAT_DELAY 500     // ms before first repeat
#define REPEAT_INTERVAL 40  // ms between repeats
#define QUOTE_RSFT_REPEAT_ON_HOLD 0
#define BSPC_SHIFT_REPEAT_ON_HOLD 1

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
  BSPC_SHIFT,
  QUOTE_RSFT,
};



#define DUAL_FUNC_0 LT(14, KC_7)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    DUAL_FUNC_0,    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,       
    CW_TOGG,        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,        
    KC_LEFT_SHIFT,  KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        QUOTE_RSFT,
    KC_LEFT_GUI,    MT(MOD_LALT, KC_Z),KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         MT(MOD_RALT, KC_SLASH),KC_RIGHT_CTRL,  
                                                    LT(1, KC_ENTER),MT(MOD_LCTL, KC_TAB),                                BSPC_SHIFT,LT(2, KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
    KC_GRAVE,       KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,                                        KC_7,           KC_8,           KC_9,           KC_MINUS,       KC_SLASH,       KC_F12,         
    KC_TRANSPARENT, KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,                                        KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_ASTR,        KC_BSPC,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_LBRC,        KC_RBRC,        KC_LCBR,        KC_RCBR,                                        KC_1,           KC_2,           KC_3,           KC_DOT,         KC_EQUAL,       KC_ENTER,       
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_0
  ),
  [2] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_CAPS,        KC_PSCR,        LCTL(LSFT(KC_PSCR)),KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_GRAVE,       KC_EXLM,        KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TILD,                                        KC_PAGE_UP,     KC_HOME,        KC_UP,          KC_END,         TT(3),          KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_EQUAL,       KC_LCBR,        KC_LPRN,        KC_RPRN,        KC_RCBR,                                        KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_SPACE,       KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_PIPE,        KC_LABK,        KC_RABK,        KC_AMPR,                                        KC_TRANSPARENT, LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR,RGB_MODE_FORWARD,RGB_SLD,        RGB_VAD,        RGB_VAI,                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT,                                 KC_PAGE_UP,     KC_HOME,        KC_UP,          KC_END,         KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT,                                 KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HSV_0_255_255,  HSV_74_255_255, HSV_169_255_255,                                KC_TRANSPARENT, LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
};



uint16_t virtual_shift = 0;
bool bspc_shift_held = false;
uint16_t bspc_shift_timer = 0;
bool bspc_shift_sent_shift = false;
uint16_t bspc_shift_repeat_timer = 0;

bool quote_rsft_held = false;
uint16_t quote_rsft_timer = 0;
bool quote_rsft_sent_shift = false;
uint16_t quote_rsft_repeat_timer = 0;
bool quote_rsft_mod_shift = false;

bool process_bspc_shift(uint16_t keycode, keyrecord_t *record) {
  if (keycode == BSPC_SHIFT) {
    if (record->event.pressed) {
        bspc_shift_held = true;
        bspc_shift_sent_shift = false;
        bspc_shift_timer = timer_read();
        if (QUOTE_RSFT_REPEAT_ON_HOLD) {
          bspc_shift_repeat_timer = bspc_shift_timer;
        }
    } else {
        if (bspc_shift_sent_shift) {
            unregister_code(KC_LSFT);
            virtual_shift--;
        } else {
            tap_code(KC_BSPC);
        }
        bspc_shift_held = false;
    }
    return false;
  }

  if (record->event.pressed && bspc_shift_held && !bspc_shift_sent_shift) {
      // Trigger shift behavior
      register_code(KC_LSFT);
      virtual_shift++;
      bspc_shift_sent_shift = true;
  }

  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = true;
  bool mod_shift = get_mods() & MOD_MASK_SHIFT;
  result  = process_bspc_shift(keycode, record) && result;
  switch (keycode) {

    case DUAL_FUNC_0:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_EQUAL);
        } else {
          unregister_code16(KC_EQUAL);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_ESCAPE);
        } else {
          unregister_code16(KC_ESCAPE);
        }  
      }  
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_0_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0,255,255);
      }
      return false;
    case HSV_74_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(74,255,255);
      }
      return false;
    case HSV_169_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(169,255,255);
      }
      return false;
    case QUOTE_RSFT:
      if (record->event.pressed) {
        quote_rsft_held = true;
        quote_rsft_sent_shift = false;
        quote_rsft_timer = timer_read();
        if (QUOTE_RSFT_REPEAT_ON_HOLD) {
          quote_rsft_repeat_timer = quote_rsft_timer;
        }
        quote_rsft_mod_shift = virtual_shift;
      } else {
        if (quote_rsft_sent_shift) {
          unregister_code(KC_RSFT);
          virtual_shift--;
        } else {
          if (!mod_shift && quote_rsft_mod_shift) {
            tap_code16(S(KC_QUOTE));
          } else {
            tap_code(KC_QUOTE);
          }
        }
        quote_rsft_held = false;
      }
      return false;

    default:
      // if another key is pressed while QUOTE_RSFT is held, trigger shift
      if (record->event.pressed && quote_rsft_held && !quote_rsft_sent_shift) {
        register_code(KC_RSFT);
        virtual_shift++;
        quote_rsft_sent_shift = true;
      }

      return result;
  }
  return result;
}

void matrix_scan_user(void) {
  if (BSPC_SHIFT_REPEAT_ON_HOLD) {
    if (bspc_shift_held && !bspc_shift_sent_shift) {
      if (timer_elapsed(bspc_shift_timer) > REPEAT_DELAY) {
        if (timer_elapsed(bspc_shift_repeat_timer) > REPEAT_INTERVAL) {
          tap_code(KC_BSPC);
          bspc_shift_repeat_timer = timer_read();
        }
      }
    }
  }

  if (QUOTE_RSFT_REPEAT_ON_HOLD) {
    if (quote_rsft_held && !quote_rsft_sent_shift) {
      if (timer_elapsed(quote_rsft_timer) > REPEAT_DELAY) {
        if (timer_elapsed(quote_rsft_repeat_timer) > REPEAT_INTERVAL) {
          tap_code(KC_QUOTE);
          quote_rsft_repeat_timer = timer_read();
        }
      }
    }
  }
}

