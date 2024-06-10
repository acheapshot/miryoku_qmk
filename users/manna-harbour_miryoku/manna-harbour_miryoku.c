// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"


// Additional Features double tap guard

enum {
    U_TD_BOOT,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL
};


//acheapshot + Miryoku combos
#include <stdint.h>

enum combo_events {
    UH_GOODDAY,
    IH_BRMC,
    THUMBCOMBOS_BASE_RIGHT,
    THUMBCOMBOS_BASE_LEFT,
    THUMBCOMBOS_NAV,
    THUMBCOMBOS_MOUSE,
    THUMBCOMBOS_MEDIA,
    THUMBCOMBOS_NUM,
    THUMBCOMBOS_SYM,
    THUMBCOMBOS_FUN
};

const uint16_t PROGMEM good_day_combo[] = {KC_U, KC_H, COMBO_END};
const uint16_t PROGMEM brmc_combo[] = {KC_I, KC_H, COMBO_END};
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT), LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(U_NAV, KC_SPC), LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN2, KC_BTN1, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
#if defined(MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
#else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
#endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};

combo_t key_combos[] = {
    [UH_GOODDAY] = COMBO_ACTION(good_day_combo),
    [IH_BRMC] = COMBO_ACTION(brmc_combo),
    [THUMBCOMBOS_BASE_RIGHT] = COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
    [THUMBCOMBOS_BASE_LEFT] = COMBO(thumbcombos_base_left, LT(U_MEDIA, KC_ESC)),
    [THUMBCOMBOS_NAV] = COMBO(thumbcombos_nav, KC_DEL),
    [THUMBCOMBOS_MOUSE] = COMBO(thumbcombos_mouse, KC_BTN3),
    [THUMBCOMBOS_MEDIA] = COMBO(thumbcombos_media, KC_MUTE),
    [THUMBCOMBOS_NUM] = COMBO(thumbcombos_num, KC_TRNS),
    [THUMBCOMBOS_SYM] = COMBO(thumbcombos_sym, KC_TRNS),
    [THUMBCOMBOS_FUN] = COMBO(thumbcombos_fun, KC_TRNS),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case UH_GOODDAY:
            if (pressed) {
                SEND_STRING("Good Day,\n\n");
            }
            break;
        case IH_BRMC:
            if (pressed) {
                SEND_STRING("Best regards,\nMatt Chesser");
            }
            break;
        // Add cases for other combo indexes as needed
    }
}
