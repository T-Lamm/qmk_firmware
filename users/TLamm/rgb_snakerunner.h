#pragma once
// directions
// -----------------------------
#include <cstdint>
// this function gives a bit map of available turns
const uint8_t left                       = 0b00000001;
const uint8_t right                      = 0b00000010;
const uint8_t up                         = 0b00000100;
const uint8_t down                       = 0b00001000;
const uint8_t reset                      = 0b00010000;
const uint8_t ready                      = 0b00100000;
const uint8_t boardsize                  = 4; // standard size is letter key + numbers no f-keys
const uint8_t firstIndexOfRow[boardsize] = {21, 42, 61, 80};

// static bool    board[10][3] = {0};                     // we define a board, is there a part of the snake or not
static uint8_t direction = reset;        // 5 inactiv; 0 left; 1 right; up 2; down 3 in which direction is the snake traveling //6 reset
static uint8_t queue[44] = {65, 64, 63}; // we build a queue of our snake bodyparts
static uint8_t snakehead = 0;
static uint8_t tail      = 2;
static uint8_t food      = 69;
uint8_t        speed     = rgb_matrix_config.speed; //// speed is defined with rgb_matrix_config.speed
static bool    cValid    = 0;

//------------------------------------------
// wrapper function
// bool snakeengine(uint8_t queue[snakehead], uint8_t* direction)//additional parameters needed

uint8_t headatedge(uint8_t direction) { // later the snakeindexarray needs to be checked
                                        // this function checks if the next moment is valid/ if when we do an additional step are still in bound
                                        // line numbers are not relativ not the absolut indexes
    uint8_t edge = 0b00000000;
    // later this needs to detect the body of the snake
    switch (direction) { // 180degree turns are not allowed
        case 0:
            edge = edge & right; // left
            break;
        case 1:
            edge = edge & left; // right
            break;
        case 2:
            edge = edge & down; // up
            break;
        case 3:
            edge = edge & up; // down
            break;
    }
    // after disallowed 180 we controll if edges are besides the head
    if ((queue[snakehead] % 4) < 1) {
        edge = edge & left;
    }
    if ((queue[snakehead] % 4) < 11) {
        edge = edge & right;
    }
    if (queue[snakehead] > 11) {
        edge = edge & up;
    }
    if (queue[snakehead] < 33) {
        edge = edge & down;
    }
    return edge;
}

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
