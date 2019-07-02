/*
Copyright 2018 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "app_ble_func.h"

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    //BACKLIT,
    //EISU,
    //KANA,
    //RGBRST

  // os
  CK_MAC,
  CK_WIN,

  // lang
  CK_A_EN,
  CK_C_JA,
};


extern keymap_config_t keymap_config;

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
#define KC_M_B1 KC_MS_BTN1
#define KC_M_B2 KC_MS_BTN2
#define KC_M_B3 KC_MS_BTN3
#define KC_NEXT C(KC_TAB)
#define KC_PREV SC(KC_TAB)
#define MOD_CTLS (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL))

enum layers {
  L_COMMON = 0,
  L_NAV,
  L_NUM,
  L_BLE
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define S_LB    SFT_T(KC_LBRC)
#define S_RB    SFT_T(KC_RBRC)
#define S_QOT   SFT_T(KC_QUOT)
#define NAV_ENT LT(L_NAV, KC_ENT)
#define GUI_SPC GUI_T(KC_SPC)
#define CTL_SPC CTL_T(KC_SPC)
#define N(kc)   LT(L_NUM,kc)
#define DOCK    C(KC_F3)
#define MENU    C(KC_F2)
#define B_GRV LT(L_BLE, KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[L_COMMON] = LAYOUT( \
KC_TAB , KC_Q   , KC_W   , KC_D   , KC_R   , KC_F   ,  KC_P   , KC_K   , KC_Y   , KC_L   , KC_SCLN, KC_BSLS,
S_QOT  , N(KC_A), N(KC_S), KC_U   , KC_T   , KC_G   ,  KC_H   , KC_N   , KC_I   , N(KC_O), N(KC_E), KC_MINS,
KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_B   , KC_V   ,  KC_J   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_KP_PLUS,
                    B_GRV, S_LB   , GUI_SPC, CK_A_EN,  CK_C_JA, NAV_ENT, S_RB   , KC_BSPC
),
[L_NAV] = LAYOUT( \
_______, _______, KC_PREV, KC_M_U , KC_NEXT, KC_HOME,  KC_END , KC_PGDN, KC_PGUP, KC_LGUI, KC_LALT, KC_SPC ,
KC_LPRN, KC_QUES, KC_M_L , KC_M_D , KC_M_R , KC_TAB ,  KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_RPRN,
_______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                  _______, KC_M_B3, KC_M_B1, KC_M_B2,  _______, _______, _______, _______
),
[L_NUM] = LAYOUT( \
_______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______,  DOCK   , KC_7   , KC_8   , KC_9   , _______, _______,
_______, KC_F5  , KC_F6,   KC_F7  , KC_F8  , KC_TAB ,  KC_EQL , KC_4   , KC_5   , KC_6   , KC_DOT , _______,
_______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______,  KC_EQL , KC_1   , KC_2   , KC_3   , _______, _______,
                  _______, _______, _______, _______,  KC_ESC , _______, KC_0   , KC_DOT
),

  [L_BLE] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
     AD_WO_L ,ADV_ID1 ,ADV_ID2 ,ADV_ID3 ,ADV_ID4 ,XXXXXXX ,     _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     ENT_SLP ,ENT_DFU ,XXXXXXX ,XXXXXXX ,USB_DIS ,USB_EN  ,     _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
     BATT_LV ,DEL_ID1 ,XXXXXXX ,XXXXXXX ,BLE_DIS ,BLE_EN  ,     _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                        _______, _______, _______, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  )
};

size_t sizeof_keymaps() {
  return sizeof(keymaps);
}

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  layer_state_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

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
  char str[16];

  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
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

  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;

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

    }
  }

  return true;
}

// Runs just one time when the keyboard initializes.
// void matrix_init_user(void) {
//   persistant_default_layer_set(1UL << L_MAC);
//   layer_move(L_QWDR);
// };
