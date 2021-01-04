#pragma once

#include <stdexcept>
#include <SDL2/SDL.h>

class Renderer {
private:
    SDL_Window *window_;
    SDL_Renderer *renderer_;

    int width_{500};
    int height_{500};

    bool running_{false};

private:
    void handle_events_();

public:
    Renderer();

    ~Renderer();

    void render();

    [[nodiscard]] inline bool is_running() const { return running_; }
};

