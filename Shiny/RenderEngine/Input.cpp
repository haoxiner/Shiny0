//
// Created by haoxin on 17/2/5.
//

#include "input.h"
#include <SDL/SDL.h>

void shiny::Input::UpdateKeyboard(const uint8_t *state) {
    leftHorizontalAxis_ = 0.0f;
    leftVerticalAxis_ = 0.0f;
    rightHorizontalAxis_ = 0.0f;
    rightVerticalAxis_ = 0.0f;
    fire0_ = false;
    test_ = false;
    jump_ = false;
    if (state[SDL_SCANCODE_A]) {
        leftHorizontalAxis_ -= 1.0f;
    }
    if (state[SDL_SCANCODE_D]) {
        leftHorizontalAxis_ += 1.0f;
    }
    if (state[SDL_SCANCODE_W]) {
        leftVerticalAxis_ += 1.0f;
    }
    if (state[SDL_SCANCODE_S]) {
        leftVerticalAxis_ -= 1.0f;
    }
    if (state[SDL_SCANCODE_UP]) {
        rightVerticalAxis_ += 1.0f;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        rightVerticalAxis_ -= 1.0f;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        rightHorizontalAxis_ -= 1.0f;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        rightHorizontalAxis_ += 1.0f;
    }
    if (state[SDL_SCANCODE_Z]) {
        fire0_ = true;
    }
    if (state[SDL_SCANCODE_T]) {
        test_ = true;
    }
    if (state[SDL_SCANCODE_Q]) {
        quit_ = true;
    }
    if (state[SDL_SCANCODE_SPACE]) {
        jump_ = true;
    }
}

void shiny::Input::UpdateMouse(unsigned int state, int x, int y) {

}

float shiny::Input::GetLeftHorizontalAxis() const {
    return leftHorizontalAxis_;
}

float shiny::Input::GetLeftVerticalAxis() const {
    return leftVerticalAxis_;
}

float shiny::Input::GetRightHorizontalAxis() const {
    return rightHorizontalAxis_;
}

float shiny::Input::GetRightVerticalAxis() const {
    return rightVerticalAxis_;
}

bool shiny::Input::Fire0() const {
    return fire0_;
}

bool shiny::Input::Test() const {
    return test_;
}

bool shiny::Input::Jump() const {
    return jump_;
}

bool shiny::Input::Quit() const {
    return quit_;
}