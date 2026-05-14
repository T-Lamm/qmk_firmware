#ifndef RGB_MATRIX_SNAKE
// TLamm costum snake effect
RGB_MATRIX_EFFECT(snakeoutput)
// left = 0; right = 1; up= 2; down = 3;
// here the board parameters are defined
const uint8_t firstIndexOfRow[3] = {21, 42, 61, 82};
// ggf there row0 for the fkeys
// row1 form 21 to 31
// row2 form 42 to 52
// row3 form 61 to 71
// row4 form 80 to 91

// this funtion gives a bit map of available turns
const unit8_t left  = 0b00000001;
const unit8_t right = 0b00000010;
const unit8_t up    = 0b00000100;
const unit8_t down  = 0b00001000;

static bool board[10][3] = {0}; // we define a board, is there a part of the snake or not
static uint8_t    direction    = 6;   // 5 inactiv; 0 left; 1 right; up 2; down 3 in which direction is the snake traveling //6 reset
static uint8_t    queue[44]    = {0}; // we build a queue of our snake bodyparts
static uint8_t    snakehead    = 66;  // start of snake maybe not static
// static uint8_t food = rng_seed
// TODO wrong datetype
///// speed is defined with rgb_matrix_config.speed


// init of this
if (direction == 6) {
    // only costomize the led backlight of the out matrix once
    static bool snakesetup(effect_params_t * params) {
        //void rgb_matrix_set_color_all()
        RGB_MATRIX_USE_LIMITS(led_min, led_max);
        for (uint8_t i = led_min; i < led_max; i++) {
            rgb_matrix_set_color(i, 0x00, 0x3F, 0xFF);
        }
    }
    direction--
}

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
            rgb_matrix_set_color(i + firstIndexOfRow[0], 0x08, 0xFF, 0xEE);
        } else { // second row
            rgb_matrix_set_color(i + firstIndexOfRow[0], 0xFF, 0x00, 0x00);
        }
        if (board[i] == 0) {
            rgb_matrix_set_color(i + firstIndexOfRow[0], 0x08, 0xFF, 0xEE);
        } else { // third row
            rgb_matrix_set_color(i + firstIndexOfRow[0], 0xFF, 0x00, 0x00);
        }
        if (board[i] == 0) {
            rgb_matrix_set_color(i + firstIndexOfRow[0], 0x08, 0xFF, 0xEE);
        } else { // fourth row
            rgb_matrix_set_color(i + firstIndexOfRow[0], 0xFF, 0x00, 0x00);
        }
    }
    // static bool rgb_matrix_set_color(){food, 0xFF, 0xFF, 0xFF};
    return rgb_matrix_check_finished_leds(led_max);
}
#endif // RGB_MATRIX_SNAKE
