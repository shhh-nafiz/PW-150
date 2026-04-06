#include <stdio.h>
#include <SDL3/SDL.h>
#include <math.h>
#include <SDL3/SDL_main.h>

#define WIDTH  800
#define HEIGHT 600
//set initial radius of circle or else it'll start from a dot or something
#define INITIAL_RADIUS 10
//assign growth speed
#define GROWTH_SPEED 0.5f
//task 101 code
void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    float step = 0.001f;
    for (float angle = 0; angle < 2 * 3.1416f; angle += step) {
        float x = cx + radius * cosf(angle);
        float y = cy + radius * sinf(angle);
        SDL_RenderPoint(renderer, x, y);
    }
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* window = SDL_CreateWindow("Growing Circle", WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    int running = 1;
    SDL_Event event;

    // radius as float so GROWTH_SPEED decimal increments work properly
    float radius = INITIAL_RADIUS;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = 0;
        }

        radius += GROWTH_SPEED;

        // circle is centered, so it hits the edge when radius reaches half of width or height
        // HEIGHT border will be touched so radius needs to be reset, but divided both by 2 for safety
        if (radius >= WIDTH / 2 || radius >= HEIGHT / 2) {
            radius = INITIAL_RADIUS;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        
        drawCircle(renderer, WIDTH / 2, HEIGHT / 2, (int)radius);

        SDL_RenderPresent(renderer);

        // SDL_Delay(Uint32 ms) pauses the program for the given number of milliseconds
        // 16ms ~ 60fps
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}