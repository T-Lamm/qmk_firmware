#ifndef RGB_MATRIX_SNAKE
//TLamm snake costum effect
RGB_MATRIX_EFFECT(snakeoutput)
//left = 0; right = 1; up= 2; down = 3;
//here the board parameters are defined
uint8_t firstIndexOfRow[3] = {21, 42, 61, 82};
//ggf there row0 for the fkeys
//row1 form 21 to 31
//row2 form 42 to 52
//row3 form 61 to 71
//row4 form 80 to 91

static bool board[10][3]={0}; //we define a bords, is there a part of the snake or not
static uint8_t direction = 5; //5 inactiv; 0 left; 1 right; up 2; down 3 in which direction is the snake traveling
static uint8_t queue[44]= {0}; //we build a queue of our snake bodyparts
static uint8_t snakehead = 66; //start of snake maybe not static
//static uint8_t food = rng_seed
//TODO wrong datetype
unit8_t headatedge(unint8_t snakehead, unint8_t direction){ // later the snakeindexarray needs to be checked
    //this function checks if the next moment is valid/ if when we do an additional step are still in bound
    //line numbers are not relativ not the absolut indexes
    //this funtion gives a bit map of available turns
    unit8_t left =  0b00000001;
    unit8_t right = 0b00000010;
    unit8_t up =    0b00000100;
    unit8_t down    0b00001000;

    unit_8 edge  = 0;
    switch(direction){ //180degree turns are not allowed
        case 0: edge =edge & right; // left
            break;
        case 1: edge =edge & left; // right
            break;
        case 2: edge =edge & down; // up
            break;
        case 3: edge =edge & up; // down
            break;
    }
    //after disallowed 180 we controll if edges are besides the head
    if(snakehead%4 < 1){
               edge = edge & left;
    }
    if(snakehead% < 11){
            edge = edge & right;
        }
    if(snakeoutput > 11){
            edge = edge & up;
        }
    if(snakehead < 33){
            edge = edge & down;
        }
    return edge;
}


void movement_to_arrowkeys(uint16_t keycode, keyrecord_t *record, uint8_t snakehead, uint8_t *direction){//current snakehead
    if(record->event.pressed){//unit16_t keycode ist schlecht
        switch(keycode){
            case KC_LEFT: //snakehead > 11
              if(headatedge(snakehead, *direction) & left != 0){
                *direction = 0;
                }
            break;

            case KC_RGHT:
              if(headatedge(snakehead, *direction) & right != 0){
                *direction = 1;
                }
            break;

            case KC_UP:
              if(headatedge(snakehead, *direction) & up != 0){
                *direction = 2;
                }
           break;

            case KC_DOWN:
              if(headatedge(snakehead, *direction) & down != 0){
                *direction = 3;
                }
            break;
        }
        return;
    }
}


//init of this
static bool snakesetup(effect_params_t* params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0x00, 0x3F, 0xFF);
  }
}


static bool snakeoutput(effect_params_t* params) { //FF FF FF als Food
  for (uint8_t i =0; i < 10; i++) {
    if(board[i] == 0){
        rgb_matrix_set_color(i+firstIndexOfRow[0], 0x08, 0xff, 0xEE);
        } else{ //first row
       rgb_matrix_set_color(i+firstIndexOfRow[0], 0xFF, 0x00, 0x00);
        }
    if(board[i] == 0){
         rgb_matrix_set_color(i+firstIndexOfRow[0], 0x08, 0xff, 0xEE);
        } else{ //second row
      rgb_matrix_set_color(i+firstIndexOfRow[0], 0xFF, 0x00, 0x00);
        }
     if(board[i] == 0){
          rgb_matrix_set_color(i+firstIndexOfRow[0], 0x08, 0xff, 0xEE);
        } else{ //third row
     rgb_matrix_set_color(i+firstIndexOfRow[0], 0xFF, 0x00, 0x00);
        }
     if(board[i] == 0){
    rgb_matrix_set_color(i+firstIndexOfRow[0], 0x08, 0xff, 0xEE);
        } else{ //fourth row
        rgb_matrix_set_color(i+firstIndexOfRow[0], 0xFF, 0x00, 0x00);
        }
    }
    //static bool rgb_matrix_set_color(){food, 0xFF, 0xFF, 0xFF};
    return rgb_matrix_check_finished_leds(led_max);
}
#endif //RGB_MATRIX_SNAKE
