//TLamm costum effect first
RGB_MATRIX_EFFECT(field_test)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//static test
static bool field_test(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i =21; i < 31; i++) {
    rgb_matrix_set_color(i, 0x08, 0xff, 0xEE);
  }
  for (uint8_t i =41; i < 52; i++) {
    rgb_matrix_set_color(i, 0x08, 0xff, 0xEE);
  }
  for (uint8_t i =61; i < 71; i++) {
    rgb_matrix_set_color(i, 0x08, 0xff, 0xEE);
  }
  for (uint8_t i =78; i < 89; i++) {
    rgb_matrix_set_color(i, 0x08, 0xff, 0xEE);
  }
  return rgb_matrix_check_finished_leds(led_max);
}
