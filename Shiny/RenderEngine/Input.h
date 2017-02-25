//
// Created by haoxin on 17/2/5.
//

#ifndef SHINY_INPUT_H
#define SHINY_INPUT_H

#include "shiny.h"
#include <cstdint>

SHINY_NAMESPACE_BEGIN

class Input {
public:
    void UpdateKeyboard(const uint8_t *state);
    void UpdateMouse(unsigned int state, int x, int y);
    float GetLeftHorizontalAxis() const;
    float GetLeftVerticalAxis() const;
    float GetRightHorizontalAxis() const;
    float GetRightVerticalAxis() const;
    bool Fire0() const;
    bool Test() const;
    bool Jump() const;
    bool Quit() const;
private:
    float leftHorizontalAxis_ = 0.0f;
    float leftVerticalAxis_ = 0.0f;
    float rightHorizontalAxis_ = 0.0f;
    float rightVerticalAxis_ = 0.0f;
    bool fire0_ = false;
    bool test_ = false;
    bool jump_ = false;
    bool quit_ = false;
};

SHINY_NAMESPACE_END

#endif //SHINY_INPUT_H
