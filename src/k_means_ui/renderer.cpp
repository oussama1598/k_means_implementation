#include "renderer.h"

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        throw std::runtime_error(SDL_GetError());

    window_ = SDL_CreateWindow(
            "Chess Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width_,
            height_,
            SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (window_ == nullptr)
        throw std::runtime_error("Could not create a window_");

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);

    if (renderer_ == nullptr)
        throw std::runtime_error("Could not create a renderer");

    running_ = true;
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Renderer::handle_events_() {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            running_ = false;
            break;
//        case SDL_MOUSEBUTTONDOWN:
//            handle_mouse_press_down_(event.button);
//            break;
//        case SDL_MOUSEBUTTONUP:
//            handle_mouse_press_up_(event.button);
//            break;
    }
}


void Renderer::render() {
    handle_events_();

    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);

    SDL_RenderPresent(renderer_);
}
