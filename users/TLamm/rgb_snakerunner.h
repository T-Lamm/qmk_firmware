#pragma once
// directions
// -----------------------------
#include <cstdint>
#include "rgb_matrix_snake.h"
// row1 form 21 to 31
// row2 form 42 to 51
// row3 form 61 to 70
// row4 form 80 to 91
//---------------------------------------
// row0 = g_led_config.matrix_co[0][1]
// row1 = g_led_config.matrix_co[1][1]
// row2 = g_led_config.matrix_co[2][1]
// row3 = g_led_config.matrix_co[3][1]
// row4 = g_led_config.matrix_co[4][1+ISO]

// this function gives a bit map of available turns
const uint8_t left                       = 0b00000001;
const uint8_t right                      = 0b00000010;
const uint8_t up                         = 0b00000100;
const uint8_t down                       = 0b00001000;
const uint8_t reset                      = 0b00010000;
const uint8_t ready                      = 0b00100000;
const uint8_t boardsize                  = 4; // standard size is letter key + numbers no f-keys
const uint8_t firstIndexOfRow[boardsize] = {21, 42, 61, 80};

// static bool    board[11][4] = {0};                     // we define a board, is there a part of the snake or not
static uint8_t direction    = reset;        // 5 inactiv; 0 left; 1 right; up 2; down 3 in which direction is the snake traveling //6 reset
static uint8_t queue[44]    = {65, 64, 63}; // we build a queue of our snake bodyparts
static uint8_t snakehead_ix = 1; //missing correct starting point
static uint8_t snakehead_iy = 1;
static uint8_t tail         = 1;
static uint8_t food         = 69;
uint8_t        speed        = rgb_matrix_config.speed; //// speed is defined with rgb_matrix_config.speed
static bool    cValid       = 0;

//------------------------------------------
// wrapper function
// bool snakeengine(uint8_t queue[snakehead], uint8_t* direction)//additional parameters needed
bool localition_is_valid() { // new definition
    if (snakehead_ix < 1) {
        direction = reset;
    } else if (snakehead_ix < 4) {
        direction = reset;
    } else if (snakehead_iy < 1) {
        direction = reset;
    } else if (snakehead_iy > 11) {
        direction = reset;
    } else {
        for (unit8_t i = 1, i >= 44 || queue[i] = 0, i++) {
            if (queue[0] == queue[i]) {
                direction = 5;
            }
        }
    }
}

bool localition_is_valid(uint8_t direction) { // later the snakeindexarray needs to be checked
                                              // this function checks if the next moment is valid/ if when we do an additional step are still in bound
                                              // line numbers are not relativ not the absolut indexes
    uint8_t edge = 0b00000000;
    // later this needs to detect the body of the snake
    for (uint8_t i = snakehead; i > tail)
        ; i--){
        if (queue[i] == queue[snakehead] && queue[i] == 0) {
            break;
        } // array is fucked, need to adjust to 0 and sizeof[queue]
    }
    // after disallowed 180 we controll if edges are besides the head
    if ((queue[snakehead] % 4) < 1 {
        edge = edge & left;
    }
    if ((queue[snakehead] % 4) < 11 {//check if correct
        edge = edge & right;
    }
    if (queue[snakehead] > g_led_config.matrix_co[1][1]) {
        edge = edge & up;
    }
    if (queue[snakehead] < g_led_config.matrix_co[3][11])) {
        edge = edge & down;
    }
    return edge;
} // better to change if the currnet position is valid; error if yes

void movement_to_arrowkeys(uint8_t clk, uint16_t keycode, keyrecord_t *record) { // current snakehead
    // here we map the the keypresses to a direction change
    // we test with headatedge if the directionchange is allowed, if not nothing happens
    // -----------------------------------
    // this needs to be clk sensitiv
    // -----------------------------------
    if (clk == 1) {
        cValid = 1;
    };
    if (cValid == 1) {
        if (record->event.pressed) {
            switch (keycode) {
                case KC_LEFT: // snakehead > 11
                    if (direction != right) {
                        direction = left;
                        cValid    = 0;
                    };
                    break;

                case KC_RGHT:
                    if (direction != left) {
                        direction = right;
                        cValid    = 0;
                    };
                    break;

                case KC_UP:
                    if (direction != down) {
                        direction = up;
                        cValid    = 0;
                    };
                    break;

                case KC_DOWN:
                    if (direction != up) {
                        direction = 3;
                        cValid    = 0;
                    };
                    break;

                case KC_PGUP: // reset
                    direction = 1;
                    snakehead = 70;
                    cValid    = 0;
                    break;

                case KC_PFGDN:
                    direction = 6;
                    cValid    = 0;
                    break;
            };
            return;
        };
    };
};
// queue has double values for foodbits
// 2 pointes for valid values
//  row1 form 21 to 31
//  row2 form 42 to 51
//  row3 form 61 to 70
//  row4 form 80 to 91
void queue_snakebody(bool clk) {
    int8_t new_snakehead;
    //  to begin of each clk_event we calculate the next position of the snakehead;
    if (clk == 1) {
        switch (direction) {
            case left:
                if (queue[snakehead] % 4 < 1) {
                    new_snakehead = --direction;
                };
                break;

            case right:
                if (queue[snakehead] % 4 > 11) {
                    new_snakehead = ++direction;
                };
                break;

            case up:
                if (queue[snakehead] > (firstIndexOfRow[0] + 11)) {
                    new_snakehead = direction - 11; // not correct yet
                };
                break;

            case down:
                if (queue[snakehead] < firstIndexOfRow[3]) {
                    new_snakehead = direction + 11; // not correct yet
                };
                break;
        };
        //  if the snake head ate food, we increase the length of the body in the next clk_event and generate a new food source
        if (food == queue[snakehead]) { // array length check 404
            queue[--tail] = queue[snakehead];
            food          = random8() & 0x00111111;
            if (food > 64) {
                food = food - 22;
            };
            // 404 compare random8 value to snakebody;
        };
        //  every game tick we move the body of the snake
        uint8_t tmp = queue[snakehead];
        snakehead++;
        tail++;
    };
};
