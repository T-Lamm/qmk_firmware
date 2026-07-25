#pragma once

//wrapper function
//bool snakeengine(uint8_t *snakehead, uint8_t* direction)//additional parameters needed

uint8_t headatedge(uint8_t snakehead, uint8_t direction) { // later the snakeindexarray needs to be checked
                                                             // this function checks if the next moment is valid/ if when we do an additional step are still in bound
                                                             // line numbers are not relativ not the absolut indexes
    unit_8 edge = 0b00000000;
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
    if (snakehead % 4 < 1) {
        edge = edge & left;
    }
    if (snakehead % < 11) {
        edge = edge & right;
    }
    if (snakeoutput > 11) {
        edge = edge & up;
    }
    if (snakehead < 33) {
        edge = edge & down;
    }
    return edge;
}

void movement_to_arrowkeys(uint16_t keycode, keyrecord_t *record, uint8_t snakehead, uint8_t *direction) { // current snakehead
    // here we map the the keypresses to a direction change
    // we test with headatedge if the directionchange is allowed, if not nothing happens
    if (record->event.pressed) {
        switch (keycode) {
            case KC_LEFT: // snakehead > 11
                if (headatedge(snakehead, *direction) & left != 0) {
                    *direction = 0;
                }
                break;

            case KC_RGHT:
                if (headatedge(snakehead, *direction) & right != 0) {
                    *direction = 1;
                }
                break;

            case KC_UP:
                if (headatedge(snakehead, *direction) & up != 0) {
                    *direction = 2;
                }
                break;

            case KC_DOWN:
                if (headatedge(snakehead, *direction) & down != 0) {
                    *direction = 3;
                }
                break;
        }
        return;
    }
}
