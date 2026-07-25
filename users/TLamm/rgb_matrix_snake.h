#ifndef RGB_MATRIX_SNAKE
// TLamm costum snake effect
RGB_MATRIX_EFFECT(snake)
// left = 0; right = 1; up= 2; down = 3;
// here the board parameters are defined
// the row with l_shift needs to be adjusted to ANSI or ISO layout
const unit8_t ISO                            = 1; // set this to 0 for ANSI
const unit8_t boardsize                      = 4; // standardsize is letter key + numbers no f-keys
const uint8_t firstIndexOfRow[boardsize - 1] = {21, 42, 61, 82};
// ggf there row0 for the fkeys
// row1 form 21 to 31
// row2 form 42 to 52
// row3 form 61 to 71
// row4 form 80 to 91
//---------------------------------------
// row0 = g_led_config.matrix_co[0][1]
// row1 = g_led_config.matrix_co[1][1]
// row2 = g_led_config.matrix_co[2][1]
// row3 = g_led_config.matrix_co[3][1]
// row4 = g_led_config.matrix_co[4][1+ISO]
//---------------------------------------

// this funtion gives a bit map of available turns
const unit8_t left  = 0b00000001;
const unit8_t right = 0b00000010;
const unit8_t up    = 0b00000100;
const unit8_t down  = 0b00001000;

static bool    board[10][3] = {0};                     // we define a board, is there a part of the snake or not
static uint8_t direction    = 6;                       // 5 inactiv; 0 left; 1 right; up 2; down 3 in which direction is the snake traveling //6 reset
static uint8_t queue[44]    = {0};                     // we build a queue of our snake bodyparts
static uint8_t snakehead    = 66;                      // start of snake maybe not static
static uint8_t food         = 22;                      // replace this with a random seed
unit8_t        speed        = rgb_matrix_config.speed; //// speed is defined with rgb_matrix_config.speed

// only customize the led backlight of the out matrix once
// as a first step the entire field gets a default color
static bool snake_init(effect_params_t *params) {
    // void rgb_matrix_set_color_all()
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0x00, 0x3F, 0xFF);
    };
    direction = 1;
    snakehead = 66;
};
static bool snakemain(effect_params_t *params) {

    for (unit_8 i = 0; i < boardsize, i++) { // colums
        for (unit8 j = 0; j < 10; j++) {     // rows
        if(boardsize[firstIndexOfRow[i] + j] == 0{
                rgb_matrix_set_color(firstIndexOfRow[0] + j, 0x08, 0xFF, 0xEE);
        } else { // first row
                rgb_matrix_set_color(firstIndexOfRow[0] + j, 0xFF, 0x00, 0x00);
        }
        }
    }
}
/*
static bool snakeoutput(effect_params_t *params) { // later use FF FF FF als food-color
    for (uint8_t i = 0; i < 10; i++) {
        // the following statements determine the coloring of each pixel
        // the snakebody has the color 0xFF0000
        // the background is 0x08ffEE
        if (board[i] == 0) {
            rgb_matrix_set_color(i + firstIndexOfRow[0], 0x08, 0xFF, 0xEE);
        } else { // first row
            rgb_matrix_set_color(i + firstIndexOfRow[0], 0xFF, 0x00, 0x00);
        }
        if (board[i] == 0) {
            rgb_matrix_set_color(i + firstIndexOfRow[1], 0x08, 0xFF, 0xEE);
        } else { // second row
            rgb_matrix_set_color(i + firstIndexOfRow[1], 0xFF, 0x00, 0x00);
        }
        if (board[i] == 0) {
            rgb_matrix_set_color(i + firstIndexOfRow[2], 0x08, 0xFF, 0xEE);
        } else { // third row
            rgb_matrix_set_color(i + firstIndexOfRow[2], 0xFF, 0x00, 0x00);
        }
        if (board[i] == 0) {
            rgb_matrix_set_color(i + firstIndexOfRow[3], 0x08, 0xFF, 0xEE);
        } else { // fourth row
            rgb_matrix_set_color(i + firstIndexOfRow[3], 0xFF, 0x00, 0x00);
        }
    }
    // static bool rgb_matrix_set_color(){food, 0xFF, 0xFF, 0xFF};
    return rgb_matrix_check_finished_leds(led_max);
}
*/
static bool snake(effect_params_t *params) {
    if (params->init) snake_init(params);
    return snakemain(params);
}
static bool
#endif // RGB_MATRIX_SNAKE
