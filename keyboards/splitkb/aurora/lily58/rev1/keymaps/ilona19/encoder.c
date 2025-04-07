#ifdef ENCODER_ENABLE
static bool     tabbing = false;
static uint16_t tabtimer;
#define TABBING_TIMER 750

bool encoder_update_user(uint8_t index, bool clockwise) {
    // 0 is left-half encoder,
    // 1 is right-half encoder
    if (index == 0) {
        if (get_mods() & MOD_BIT(KC_LEFT_CTRL)) {
            // Left rotate = brightness
            if (clockwise) {
                tap_code(KC_BRIGHTNESS_UP);
            } else {
                tap_code(KC_BRIGHTNESS_DOWN);
            }
        } else {
            // control + Left rotate = volume
            if (clockwise) {
                tap_code(KC_AUDIO_VOL_UP);
            } else {
                tap_code(KC_AUDIO_VOL_DOWN);
            }
        }

    } else if (index == 1) {
        // app switch
        if (clockwise) {
            tabtimer = timer_read();
            if (!tabbing) {
                register_code(KC_LALT);
                tabbing = true;
            }
            tap_code(KC_TAB);
        } else {
            tabtimer = timer_read();
            if (!tabbing) {
                register_code(KC_LALT);
                tabbing = true;
            }
            register_code(KC_LSFT);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
        }
    }
    return false;
}
void matrix_scan_user(void) {
    if (tabbing) {
        if (timer_elapsed(tabtimer) > TABBING_TIMER) {
            unregister_code(KC_LALT);
            tabbing = false;
        }
    }
}
#endif