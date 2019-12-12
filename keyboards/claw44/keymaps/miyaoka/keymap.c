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

// Fillers to make layering clearer
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define S_LB    SFT_T(KC_LBRC)
#define S_RB    SFT_T(KC_RBRC)
#define S_QOT   SFT_T(KC_QUOT)
#define C_GRV   CTL_T(KC_GRV)
#define NAV_ENT LT(L_NAV, KC_ENT)
#define GUI_SPC GUI_T(KC_SPC)
#define CTL_SPC CTL_T(KC_SPC)
#define N(kc)   LT(L_NUM,kc)
#define DOCK    C(KC_F3)
#define MENU    C(KC_F2)
#define CAP     S(LGUI(KC_4)) // Mac screen shot

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[L_COMMON] = LAYOUT( \
KC_TAB , _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_BSLS,
S_QOT  , _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_MINS,
KC_LSFT, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, KC_KP_PLUS,
                    C_GRV, S_LB   , _______, CK_A_EN,  CK_C_JA, NAV_ENT, S_RB   , KC_BSPC
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
_______, N(KC_A), N(KC_S), KC_U   , KC_T   , KC_G   ,  KC_H   , KC_N   , KC_I   , N(KC_O), N(KC_E), _______,
_______, KC_Z   , KC_X   , KC_C   , KC_B   , KC_V   ,  KC_J   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
                  _______, _______, _______, _______,  _______, _______, _______, _______
),
[L_NAV] = LAYOUT( \
CAP    , _______, KC_PREV, KC_M_U , KC_NEXT, KC_END ,  KC_HOME, KC_PGDN, KC_PGUP, KC_LGUI, KC_LALT, KC_SPC ,
KC_LPRN, KC_QUES, KC_M_L , KC_M_D , KC_M_R , KC_TAB ,  KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_RPRN,
_______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                  _______, KC_M_B3, KC_M_B1, KC_M_B2,  _______, _______, _______, _______
),
[L_NUM] = LAYOUT( \
_______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______,  DOCK   , KC_7   , KC_8   , KC_9   , _______, _______,
_______, KC_F5  , KC_F6,   KC_F7  , KC_F8  , KC_TAB ,  KC_EQL , KC_4   , KC_5   , KC_6   , KC_ESC , _______,
_______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,  KC_EQL , KC_1   , KC_2   , KC_3   , _______, _______,
                  _______, _______, _______, KC_ESC ,  KC_ESC , _______, KC_0   , KC_DOT
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

static bool en_pressed = false;
static bool ja_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if(record->event.pressed){
    switch (keycode) {
    //--layers--

    // os
    case CK_MAC:
      persistant_default_layer_set(1UL << L_MAC);
      return false;
    case CK_WIN:
      persistant_default_layer_set(1UL << L_WIN);
      return false;

    // langs
    case CK_A_EN:
      en_pressed = true;
      add_mods(MOD_BIT(KC_LALT));
      return false;

    case CK_C_JA:
      ja_pressed = true;
      add_mods(MOD_BIT(KC_RCTL));
      return false;

    // Ctrl-Q -> Alt-F4
    case KC_Q:
      if (get_mods() & MOD_CTLS) {
        clear_keyboard();
        add_mods(MOD_BIT(KC_LALT));
        type_code(KC_F4);
        del_mods(MOD_BIT(KC_LALT));
        return false;
      }
      break;
    default:
      en_pressed = false;
      ja_pressed = false;
    }
  } else if (!record->event.pressed) {
    switch (keycode) {

    case CK_A_EN:
      if (en_pressed) {
        del_mods(MOD_BIT(KC_LALT));
        set_eisu();
      } else {
        unregister_code(KC_LALT);
      }
      en_pressed = false;
      return false;

    case CK_C_JA:
      if (ja_pressed) {
        del_mods(MOD_BIT(KC_RCTL));
        set_kana();
      } else {
        unregister_code(KC_RCTL);
      }
      ja_pressed = false;
      return false;
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  persistant_default_layer_set(1UL << L_MAC);
  layer_move(L_QWDR);
};
