#pragma once

#include <stdexcept>
#include <SDL2/SDL.h>
#include <vector>
#include <math/point.h>
#include <k_means/k_means.h>
#include <map>

class Renderer {
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;

    std::string _title{"K-Means Implementation"};

    int _width{500};
    int _height{500};

    std::vector<Point> _points;

    bool _running{false};

    KMeans _kmeans{2, _width, _height, _points};

    std::map<int, SDL_Color> _colors{
            {0, {255, 0, 0,   255}},
            {1, {0,   0, 255, 255}}
    };

private:
    void _handle_events();

    void _handle_mouse_press_up(SDL_MouseButtonEvent &event);

public:
    Renderer();

    ~Renderer();

    void render();

    [[nodiscard]] inline bool is_running() const { return _running; }
};

