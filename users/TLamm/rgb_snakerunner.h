#pragma once
// directions
const unit8_t left  = 0b00000001;
const unit8_t right = 0b00000010;
const unit8_t up    = 0b00000100;
const unit8_t down  = 0b00001000;

// wrapper function
// bool snakeengine(uint8_t *snakehead, uint8_t* direction)//additional parameters needed

uint8_t headatedge(uint8_t snakehead, uint8_t direction) { // later the snakeindexarray needs to be checked
                                                           // this function checks if the next moment is valid/ if when we do an additional step are still in bound
                                                           // line numbers are not relativ not the absolut indexes
    unit_8 edge = 0b00000000;
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
    if ((snakehead % 4) < 1) {
        edge = edge & left;
    }
    if ((snakehead % 4) < 11) {
        edge = edge & right;
    }
    if (snakehead > 11) {
        edge = edge & up;
    }
    if (snakehead < 33) {
        edge = edge & down;
    }
    return edge;
}

void movement_to_arrowkeys(uint16_t keycode, keyrecord_t *record) { // current snakehead
    // here we map the the keypresses to a direction change
    // we test with headatedge if the directionchange is allowed, if not nothing happens
    if (record->event.pressed) {
        switch (keycode) {
            case KC_LEFT: // snakehead > 11
                if (direction != right) {
                    direction = left;
                }
                break;

            case KC_RGHT:
                if (direction != left) {
                    direction = right;
                }
                break;

            case KC_UP:
                if (direction != down) {
                    direction = up;
                }
                break;

            case KC_DOWN:
                if (direction != up) {
                    direction = 3;
                }
                break;

            case KC_PGUP: // reset
                direction = 1;
                snakehead = 70;
                break;

            case KC_PFGDN:
                direction = 6;
                break;
        }
        return;
    }
}

void queue_snakebody(bool clk) {
    if (clk == 1) {
        switch (direction) { case left: }
    }
    food = random8();
}

)
