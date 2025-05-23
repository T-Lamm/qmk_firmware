#ifdef RGB_MATRIX_SNAKE
//TLamm costum effect first
RGB_MATRIX_EFFECT(field_test)
////////////////////////////////////what the fuck is wrong here

//static test
//the following numbers indicate the gamefield for the q6
//21 to 31
uint8_t row0 = 21;
//42 to 52
uint8_t row1 = 42;
//61 to 71
uint8_t row2 = 61;
//80 to 91
uint8_t row3 = 82;
//uint8_t board[10][3]={0};
uint8_t direction = 0; //0 inactiv; 1 left; 2 up; 3 down; 4 right;
uint8_t queue[44]= {0};

bool is_movement_valid(unit8_t snakehead, unit8_t direction){ // later the snakeindexarray needs to be checked
    switch(direction){
        case 1: //left
            if(snakehead%4 > 1){
                return 1;
            }
            break;

        case 2: //up
            if(snakehead > 11){
                return 1;
            }
            break;

        case 3: //down
            if(snakehead < 33){
                return 1;
            break;
            }
        case 4: //right
            if(snakehead%4 < 11 ){
                return 1;
            }
            break;
    }
}


uint8 snakehead = 20;
bool movement_to_arrowkeys(uint16_t keycode, keyrecord_t *record, uint8_t *snakehead, uint8_t *direction){//current snakehead
    if(record->event.pressed){//unit16_t keycode ist schlecht
        switch(keycode){
            case KC_UP: //snakehead > 11
            if(is_movement_valid(direction) == 1){
                snakehead= snakehead -11;
            }
            break;

            case KC_DOWN:
            if(is_movement_valid(direction) == 1){
                snakehead = snakehead + 11;
            }
            break;

            case KC_RGHT:
            if(is_movement_valid(direction) == 1){
                snakehead = snakehead +1;
            }
            break;

            case KC_LEFT:
            if(is_movement_valid(direction) == 1){
                sankhead = snakehead -1;
            break;
            }
        }
    }
    return true;
}


static bool field_test(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i =led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
  }
  for (uint8_t i =0; i < 10; i++) {
    rgb_matrix_set_color(i+row0, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+row1, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+row2, 0x08, 0xff, 0xEE);
    rgb_matrix_set_color(i+row3, 0x08, 0xff, 0xEE);
  }
  return rgb_matrix_check_finished_leds(led_max);
}
#endif //RGB_MATRIX_SNAKE
