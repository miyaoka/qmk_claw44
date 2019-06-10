#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#  include "lufa.h"
#  include "split_util.h"
#endif
#ifdef SSD1306OLED
#  include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Alias
#define C(kc) LCTL(kc)
#define A(kc) LALT(kc)
#define SC(kc) (S(C(kc)))
#define SA(kc) (S(A(kc)))
#define KC_M_WU KC_MS_WH_UP
#define KC_M_WD KC_MS_WH_DOWN
#define KC_M_WL KC_MS_WH_LEFT
#define KC_M_WR KC_MS_WH_RIGHT
#define KC_M_U KC_MS_U
#define KC_M_D KC_MS_D
#define KC_M_L KC_MS_L
#define KC_M_R KC_MS_R
#define KC_M_A0 KC_MS_ACCEL0
#define KC_M_A1 KC_MS_ACCEL1
#define KC_M_A2 KC_MS_ACCEL2
#define KC_M_B1 KC_MS_BTN1
#define KC_M_B2 KC_MS_BTN2
#define KC_M_B3 KC_MS_BTN3
#define KC_NEXT C(KC_TAB)
#define KC_PREV SC(KC_TAB)
#define MOD_CTLS (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL))

// Layers
enum layers {
  L_COMMON = 0,
  L_MAC,
  L_WIN,
  L_QWDR,
  L_NAV,
  L_NUM
};

enum custom_keycodes {
  //--layers--
  // layoutsp
  CK_GAME = SAFE_RANGE,
  CK_LNAV2,

  // os
  CK_MAC,
  CK_WIN,

  // lang
  CK_A_EN,
  CK_C_JA,
};

uint16_t hold_timers[MATRIX_ROWS][MATRIX_COLS];

// Fillers to make layering clearer
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define S_LB    SFT_T(KC_LBRC)
#define S_RB    SFT_T(KC_RBRC)
#define S_QOT   SFT_T(KC_QUOT)
#define NAV_ENT LT(L_NAV, KC_ENT)
#define GUI_SPC GUI_T(KC_SPC)
#define CTL_SPC CTL_T(KC_SPC)
#define NUM_A   LT(L_NUM,KC_A)
#define NUM_S   LT(L_NUM,KC_S)
#define NUM_O   LT(L_NUM,KC_O)
#define NUM_E   LT(L_NUM,KC_E)
#define DOCK    C(KC_F3)
#define MENU    C(KC_F2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[L_COMMON] = LAYOUT( \
KC_TAB , _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_BSLS,
S_QOT  , _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_MINS,
KC_LSFT, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_KP_PLUS,
                   KC_GRV, S_LB   , _______, CK_A_EN,  CK_C_JA, NAV_ENT, S_RB   , KC_BSPC
),
[L_MAC] = LAYOUT( \
_______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
                  _______, _______, GUI_SPC, _______,  _______, _______, _______, _______
),
[L_WIN] = LAYOUT( \
_______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
_______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
                  _______, _______, CTL_SPC, _______,  _______, _______, _______, _______
),
[L_QWDR] = LAYOUT( \
_______, KC_Q   , KC_W   , KC_D   , KC_R   , KC_F   ,  KC_P   , KC_K   , KC_Y   , KC_L   , KC_SCLN, _______,
_______, NUM_A  , NUM_S  , KC_U   , KC_T   , KC_G   ,  KC_H   , KC_N   , KC_I   , NUM_O  , NUM_E  , _______,
_______, KC_Z   , KC_X   , KC_C   , KC_B   , KC_V   ,  KC_J   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
                  _______, _______, _______, _______,  _______, _______, _______, _______
),
[L_NAV] = LAYOUT( \
_______, _______, KC_PREV, KC_M_U , KC_NEXT, KC_HOME,  KC_END , KC_PGDN, KC_PGUP, KC_SPC , KC_LALT, KC_LGUI,
KC_LPRN, KC_QUES, KC_M_L , KC_M_D , KC_M_R , KC_TAB ,  KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_RPRN,
_______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                  _______, KC_M_B3, KC_M_B1, KC_M_B2,  _______, _______, _______, _______
),
[L_NUM] = LAYOUT( \
KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,  DOCK   , KC_7   , KC_8   , KC_9   , _______, _______,
KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,  KC_EQL , KC_4   , KC_5   , KC_6   , KC_ESC , _______,
_______, _______, _______, _______, _______, _______,  KC_EQL , KC_1   , KC_2   , KC_3   , _______, _______,
                  _______, _______, _______, _______,  _______, _______, KC_0   , KC_DOT
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void switch_layer(uint8_t layer, bool on) {
  if (on) {
    layer_on(layer);
  } else {
    layer_off(layer);
  }
};

void type_code(uint8_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
};

void set_eisu(void) {
  type_code(KC_MHEN);
  type_code(KC_LANG2);
};

void set_kana(void) {
  type_code(KC_HENK);
  type_code(KC_LANG1);
};

bool is_tap(keyrecord_t *record) { return hold_timers[record->event.key.row][record->event.key.col] && timer_elapsed(hold_timers[record->event.key.row][record->event.key.col]) < TAPPING_TERM; }

void mod_tap_action(keyrecord_t *record, uint8_t mod, void (*cb)(void)) {
  if (record->event.pressed) {
    add_mods(MOD_BIT(mod));
  } else {
    if (is_tap(record)) {
      del_mods(MOD_BIT(mod));
      cb();
    } else {
      unregister_code(mod);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // record pressed timer
  if (record->event.pressed) {
    hold_timers[record->event.key.row][record->event.key.col] = timer_read();
  }

  switch (keycode) {
    //--layers--

    // os
    case CK_MAC:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL << L_MAC);
      }
      return false;
      break;
    case CK_WIN:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL << L_WIN);
      }
      return false;
      break;

    // langs
    case CK_A_EN:
      mod_tap_action(record, KC_LALT, set_eisu);
      return false;
      break;
    case CK_C_JA:
      mod_tap_action(record, KC_RCTL, set_kana);
      return false;
      break;

    // Ctrl-Q -> Alt-F4
    case KC_Q:
      if (record->event.pressed && (get_mods() & MOD_CTLS)) {
        clear_keyboard();
        add_mods(MOD_BIT(KC_LALT));
        type_code(KC_F4);
        del_mods(MOD_BIT(KC_LALT));
        return false;
      }
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  persistant_default_layer_set(1UL << L_MAC);
  layer_move(L_QWDR);
};
