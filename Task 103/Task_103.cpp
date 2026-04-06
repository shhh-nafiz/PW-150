#include <stdio.h>
#include <SDL3/SDL.h>
#include <math.h>
#include <SDL3/SDL_main.h>

#define WIDTH       800
#define HEIGHT      600
//set radius px
#define RADIUS      40
//set movespeed for keys
#define MOVE_SPEED  4

void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    float step = 0.01f;
    for (float angle = 0; angle < 2 * 3.1416f; angle += step) {
        float x = cx + radius * cosf(angle);
        float y = cy + radius * sinf(angle);
        SDL_RenderPoint(renderer, x, y);
    }
}

// distance between two centers, if less than combined radii they are overlapping
int checkCollision(int x1, int y1, int x2, int y2, int r1, int r2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    //distance between 2 points formula
    float distance = sqrtf((float)(dx * dx + dy * dy));
    return distance <= (r1+r2);
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* window = SDL_CreateWindow("Collision", WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    int running = 1;
    SDL_Event event;

    //circle 1, automatically moves left to right in the center of window
    float c1x = 0;
    float c1y = HEIGHT / 2;

    //circle 2 user controlled, starts at middle top of window
    float c2x = WIDTH / 2;
    float c2y = 0;

    int collision = 0;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = 0;
        }

        //SDL_GetKeyboardState(NULL) returns a snapshot ARRAY(incase multiple pressed at once) of every keys current state
        //NULL means we dont need the key count returned, index with SDL_SCANCODE_*the_literal_key to check a key
        //1 = currently held, 0 = not held, checked every frame so movement is smooth
        const bool* keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_UP])    c2y -= MOVE_SPEED;
        if (keys[SDL_SCANCODE_DOWN])  c2y += MOVE_SPEED;
        if (keys[SDL_SCANCODE_LEFT])  c2x -= MOVE_SPEED;
        if (keys[SDL_SCANCODE_RIGHT]) c2x += MOVE_SPEED;

        //move circle 1 when it passes  the right edge reset it to the left
        c1x += 3;
        if (c1x - RADIUS > WIDTH) c1x = -(float) RADIUS;

        collision = checkCollision((int)c1x, (int)c1y, (int)c2x, (int)c2y, RADIUS, RADIUS);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //on collision both circles turn white, otherwise their normal colors
        SDL_SetRenderDrawColor(renderer, collision ? 255 : 255, collision ? 255 : 0, collision ? 255 : 0, 255);
        drawCircle(renderer, (int)c1x, (int)c1y, RADIUS);

        SDL_SetRenderDrawColor(renderer, collision ? 255 : 0, collision ? 255 : 150, collision ? 255 : 255, 255);
        drawCircle(renderer, (int)c2x, (int)c2y, RADIUS);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}