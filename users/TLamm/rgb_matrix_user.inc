//TLamm costum effect first
RGB_MATRIX_EFFECT(field_test)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

//static test
//Q6 field parameters |K3 pro parameters
//21 to 31            |17 to 27
//42 to 52            |32 to 42
//61 to 71            |47 to 57
//80 to 91            |61 to 71
static bool field_test(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i =led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
  }
  for (uint8_t i =0; i < 10; i++) {
    rgb_matrix_set_color(i+17, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+32, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+47, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+62, 0x08, 0xff, 0xEE);
  }
  return rgb_matrix_check_finished_leds(led_max);
}
#endif //RGB_MATRIX_CUSTOM_EFFECT_IMPLS
