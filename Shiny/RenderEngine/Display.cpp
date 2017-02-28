//
// Created by haoxin on 17/2/1.
//

#include "Display.h"
#include <opengl.h>
#include <sstream>

bool shiny::Display::Startup(int xResolution, int yResolution) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);

    window_ = SDL_CreateWindow("shiny", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, xResolution, yResolution, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window_ == nullptr) {
        return false;
    }
    SDL_GLContext glContext = SDL_GL_CreateContext(window_);
    if (!glContext) {
        return false;
    }
    if (SDL_GL_SetSwapInterval(1) < 0) {
        return false;
    }
    //SDL_GL_SetSwapInterval(0);
//    SDL_SetRelativeMouseMode(SDL_TRUE);
	glewExperimental = true;
	glewInit();

    running_ = true;
    return true;
}

void shiny::Display::Update() {
    SDL_GL_SwapWindow(window_);
    SDL_Event event;
    if (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            running_ = false;
        }
        input_.UpdateKeyboard(SDL_GetKeyboardState(nullptr));
    }
}

void shiny::Display::Shutdown() {
    running_ = false;
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    SDL_Quit();
}

bool shiny::Display::Running() {
    return running_;
}

const shiny::Input *shiny::Display::GetInput() const {
    return &input_;
}