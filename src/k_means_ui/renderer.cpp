#include "renderer.h"

Renderer::Renderer() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        throw std::runtime_error(SDL_GetError());

    _window = SDL_CreateWindow(
            _title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            (int) _width,
            _height,
            SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (_window == nullptr)
        throw std::runtime_error("Could not create a _window");

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (_renderer == nullptr)
        throw std::runtime_error("Could not create a renderer");

    _running = true;
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Renderer::_handle_mouse_press_up(SDL_MouseButtonEvent &event) {
    if (event.button == SDL_BUTTON_RIGHT) {
        _points.push_back({event.x, event.y});
    }
}

void Renderer::_handle_events() {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            _running = false;
            break;
        case SDL_MOUSEBUTTONUP:
            _handle_mouse_press_up(event.button);
            break;
    }
}


void Renderer::render() {
    _handle_events();

    _kmeans.tick();

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    for (auto &point: _points) {
        SDL_Color &color = _colors[point.centroid];
        SDL_Rect rect = {point.x, point.y, 10, 10};

        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(_renderer, &rect);
    }

    SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);

    for (auto &centroid: _kmeans.get_centroids()) {
        SDL_Color &color = _colors[centroid.id];
        SDL_Rect rect = {centroid.x, centroid.y, 10, 10};

        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(_renderer, &rect);
    }

    SDL_RenderPresent(_renderer);
}
