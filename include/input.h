#pragma once;

struct Input {
    bool up;
    bool down;
    bool left;
    bool right;
};

void clearInput(Input &input) {
    input.up = false;
    input.down = false;
    input.left = false;
    input.right = false;
}



