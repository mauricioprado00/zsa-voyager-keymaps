#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

#define REPEAT_DELAY 500     // ms before first repeat
#define REPEAT_INTERVAL 40  // ms between repeats
#define SCLN_RSFT_REPEAT_ON_HOLD 0
#define BSPC_SHIFT_REPEAT_ON_HOLD 1
#define SCLN_RSFT_TAP_CODE KC_SCLN
#define DUAL_FUNC_0 LT(14, KC_7)
#define I_RSFT_REPEAT_ON_HOLD 0
#define I_RSFT_TAP_CODE KC_I

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
  BSPC_SHIFT,
  SCLN_RSFT,
  I_RSFT,
};



enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
};

#define DUAL_FUNC_0 LT(4, KC_0)
#define DUAL_FUNC_1 LT(5, KC_F10)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_EQUAL,       KC_1,           KC_2,           TD(DANCE_0),    KC_4,           KC_5,                                           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,       
    KC_TRANSPARENT, KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,                                           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLS,        
    KC_LEFT_SHIFT,  KC_A,           KC_S,           KC_D,           KC_F,           KC_G,                                           KC_H,           KC_J,           KC_K,           KC_L,           SCLN_RSFT,KC_QUOTE,       
    KC_LEFT_GUI,    MT(MOD_LALT, KC_Z),KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         MT(MOD_RALT, KC_SLASH),KC_RIGHT_CTRL,  
                                                    LT(1, KC_ENTER),MT(MOD_LCTL, KC_TAB),                                BSPC_SHIFT,LT(2, KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,                                          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
    KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,                                        KC_7,           KC_8,           KC_9,           KC_MINUS,       KC_SLASH,       KC_F12,         
    KC_ESCAPE,      KC_GRAVE,       KC_AMPR,        KC_ASTR,        KC_TILD,        KC_PIPE,                                        KC_4,           KC_5,           KC_6,           KC_PLUS,        KC_ASTR,        KC_BSPC,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_1,           KC_2,           KC_3,           KC_DOT,         KC_EQUAL,       KC_ENTER,       
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_0
  ),
  [2] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_CAPS,        KC_PSCR,        LCTL(LSFT(KC_PSCR)),KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_DELETE,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_EXLM,        KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TRANSPARENT,                                 KC_PAGE_UP,     KC_HOME,        KC_UP,          KC_END,         TT(3),          KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_EQUAL,       KC_LCBR,        KC_LPRN,        KC_RPRN,        KC_RCBR,                                        KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_SPACE,       KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LABK,        KC_RABK,        KC_TRANSPARENT,                                 KC_TRANSPARENT, LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR,RGB_MODE_FORWARD,RGB_SLD,        RGB_VAD,        RGB_VAI,                                        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,  KC_TRANSPARENT,                                 KC_PAGE_UP,     KC_HOME,        KC_UP,          KC_END,         KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT,                                 KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HSV_0_255_255,  HSV_74_255_255, HSV_169_255_255,                                KC_TRANSPARENT, LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_1),    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_Q,           KC_D,           KC_R,           KC_W,           KC_B,                                           KC_J,           KC_F,           KC_U,           KC_P,           KC_SCLN,        KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_A,           KC_S,           KC_H,           KC_T,           KC_G,                                           KC_Y,           KC_N,           KC_E,           KC_O,           I_RSFT,KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_X,           KC_M,           KC_C,           KC_V,                                           KC_K,           KC_L,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    DUAL_FUNC_0,    KC_TRANSPARENT,                                 KC_TRANSPARENT, DUAL_FUNC_1
  ),
};








typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[2];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_3);
        tap_code16(KC_3);
        tap_code16(KC_3);
    }
    if(state->count > 3) {
        tap_code16(KC_3);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_3); break;
        case DOUBLE_TAP: layer_move(4); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_3); register_code16(KC_3);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_3); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_3); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_3);
        tap_code16(KC_3);
        tap_code16(KC_3);
    }
    if(state->count > 3) {
        tap_code16(KC_3);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_3); break;
        case DOUBLE_TAP: layer_move(0); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_3); register_code16(KC_3);
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_3); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_3); break;
    }
    dance_state[1].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
};



uint16_t virtual_shift = 0;
bool bspc_shift_held = false;
uint16_t bspc_shift_timer = 0;
bool bspc_shift_sent_shift = false;
uint16_t bspc_shift_repeat_timer = 0;

bool scln_rsft_sent_tap = false;
bool scln_rsft_held = false;
uint16_t scln_rsft_timer = 0;
bool scln_rsft_sent_shift = false;
uint16_t scln_rsft_repeat_timer = 0;
bool scln_rsft_mod_shift = false;

bool process_bspc_shift(uint16_t keycode, keyrecord_t *record) {
  if (keycode == BSPC_SHIFT) {
    if (record->event.pressed) {
        bspc_shift_held = true;
        bspc_shift_sent_shift = false;
        bspc_shift_timer = timer_read();
        if (SCLN_RSFT_REPEAT_ON_HOLD) {
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
    case SCLN_RSFT:
      if (record->event.pressed) {
        if (mod_shift) {
          scln_rsft_sent_tap = true;
          tap_code(SCLN_RSFT_TAP_CODE);
        } else {
          scln_rsft_sent_tap = false;
          scln_rsft_held = true;
          scln_rsft_sent_shift = false;
          scln_rsft_timer = timer_read();
          if (SCLN_RSFT_REPEAT_ON_HOLD) {
            scln_rsft_repeat_timer = scln_rsft_timer;
          }
          scln_rsft_mod_shift = virtual_shift;
        }
      } else {
        if (scln_rsft_sent_tap) {
          // nothing to do, all done already.
        } else if (scln_rsft_sent_shift) {
          unregister_code(KC_RSFT);
          virtual_shift--;
        } else {
          if (!mod_shift && scln_rsft_mod_shift) {
            tap_code16(S(SCLN_RSFT_TAP_CODE));
          } else {
            tap_code(SCLN_RSFT_TAP_CODE);
          }
        }
        scln_rsft_held = false;
      }
      return false;

    case I_RSFT:
      if (record->event.pressed) {
        if (mod_shift) {
          scln_rsft_sent_tap = true;
          tap_code(I_RSFT_TAP_CODE);
        } else {
          scln_rsft_sent_tap = false;
          scln_rsft_held = true;
          scln_rsft_sent_shift = false;
          scln_rsft_timer = timer_read();
          if (I_RSFT_REPEAT_ON_HOLD) {
            scln_rsft_repeat_timer = scln_rsft_timer;
          }
          scln_rsft_mod_shift = virtual_shift;
        }
      } else {
        if (scln_rsft_sent_tap) {
          // nothing to do, all done already.
        } else if (scln_rsft_sent_shift) {
          unregister_code(KC_RSFT);
          virtual_shift--;
        } else {
          if (!mod_shift && scln_rsft_mod_shift) {
            tap_code16(S(I_RSFT_TAP_CODE));
          } else {
            tap_code(I_RSFT_TAP_CODE);
          }
        }
        scln_rsft_held = false;
      }
      return false;

    default:
      // if another key is pressed while SCLN_RSFT is held, trigger shift
      if (record->event.pressed && scln_rsft_held && !scln_rsft_sent_shift) {
        register_code(KC_RSFT);
        virtual_shift++;
        scln_rsft_sent_shift = true;
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

  if (SCLN_RSFT_REPEAT_ON_HOLD) {
    if (scln_rsft_held && !scln_rsft_sent_shift) {
      if (timer_elapsed(scln_rsft_timer) > REPEAT_DELAY) {
        if (timer_elapsed(scln_rsft_repeat_timer) > REPEAT_INTERVAL) {
          tap_code(SCLN_RSFT_TAP_CODE);
          scln_rsft_repeat_timer = timer_read();
        }
      }
    }
  }

  if (I_RSFT_REPEAT_ON_HOLD) {
    if (scln_rsft_held && !scln_rsft_sent_shift) {
      if (timer_elapsed(scln_rsft_timer) > REPEAT_DELAY) {
        if (timer_elapsed(scln_rsft_repeat_timer) > REPEAT_INTERVAL) {
          tap_code(I_RSFT_TAP_CODE);
          scln_rsft_repeat_timer = timer_read();
        }
      }
    }
  }
}
