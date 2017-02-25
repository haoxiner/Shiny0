//
// Created by haoxin on 17/2/1.
//

#ifndef SHINY_DISPLAY_H
#define SHINY_DISPLAY_H

#include "shiny.h"
#include "input.h"
#include <SDL/SDL.h>

SHINY_NAMESPACE_BEGIN

class Display {
public:
    bool Startup(int xResolution, int yResolution);
    void Update();
    void Shutdown();
    bool Running();
    const Input *GetInput() const;
private:
    bool running_ = false;
    SDL_Window *window_ = nullptr;
    Input input_;
};

SHINY_NAMESPACE_END

#endif //SHINY_DISPLAY_H
