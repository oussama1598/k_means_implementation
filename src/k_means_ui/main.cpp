#include "renderer.h"

int main() {
    Renderer renderer;

    while(renderer.is_running())
        renderer.render();
}
