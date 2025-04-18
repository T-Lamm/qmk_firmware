//TLamm costum effect first
RGB_MATRIX_EFFECT(field_test)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//static test
//21 to 31
//42 to 52
//61 to 71
//80 to 91
static bool field_test(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i =led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
  }
  for (uint8_t i =0; i < 10; i++) {
    rgb_matrix_set_color(i+21, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+42, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+61, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+80, 0x08, 0xff, 0xEE);
  }
  return rgb_matrix_check_finished_leds(led_max);
}
#endif //RGB_MATRIX_CUSTOM_EFFECT_IMPLS
