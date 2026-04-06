#include <stdio.h>
#include  <SDl3/SDL.h>
#include <math.h>
// link sdl then include it as shown here( to link do the property thing(linkers->), make sure to paste the SDL3.dll where the .cpp file is)
#include  <SDl3/SDL_main.h>
// set resolution of the window b4 hand
#define WIDTH  800
#define HEIGHT 600


void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    // step through the circle bit by bit. 
       // increasing 'step' makes the circle smoother but slower to draw.
    float step = 0.01f;

    // loop from 0 to 2*pi means a full 360 degree rotation

    for (float angle = 0; angle < 2 * 3.1416; angle += step) {

        // Calculate the x and y position of the dot
        // cos gives us the horizontal distance, sin gives us the vertical
        //sin() for in, sinf() for float, using f is a good practice basically( for float numbers) 
        float x = cx + radius * cosf(angle);
        float y = cy + radius * sinf(angle);
        // x= centerX =(radius* cos(angle)) vice versa for y is the formula to find edge of a circle
        // render the dot (point)
        SDL_RenderPoint(renderer, x, y);
    }
}

int main(int argc, char* args[])
//needs to include both of these parameters, in linkers dont include SDL3main.lib, sdl3 doesntneed it
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); //SDL_INIT_EVERYTHING DOESNT WORK IN SDL3
    //printf("hello world"); SDL_Init boots up sdl3 subsystems
    // SDL_CreateWindow(title of window, width, height, flag(basically presets for window type, size etc)
    // SDL_Window, represents the window struct
    SDL_Window* window = SDL_CreateWindow("Circle", WIDTH, HEIGHT, 0);

    // SDL3: second arg is renderer name, NULL = pick best one(vulcan, directx etc)
    //SDL_Renderer, link between code and GPU struct
    //SDL_CreateRenderer(name of window to draw in, what driver to use);
    // we use pointers on the members of struct when carried out by OS
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    int running = 1;
    //SDL_Event is a struct that stores a packet of data from the Operating System's input queue.
    // basically required for recording inputs, no pointer needed as its a function taken out by us than the OS
    SDL_Event event;
    //start of game loop
    while (running) {
        // & used as event wasnt a pointer, so with & SDL can access
        //bool SDL_PollEvent(SDL_Event * event), this func moves the recorded inputs from os to program
        while (SDL_PollEvent(&event)) {
            // event.type struct variable, 
            if (event.type == SDL_EVENT_QUIT) running = 0;
        }

        //bool SDL_SetRenderDrawColor(SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        //active color of renderer
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        //SDL_RenderClear(*SDL_Renderer).. clears the renderer to current renderer color
        SDL_RenderClear(renderer);

        // change color
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        //draw the circle according to func
        drawCircle(renderer, WIDTH / 2, HEIGHT / 2, 100);
        //SDL_RenderPresent(*SDL_Renderer) basically swaps back buffer to screen, user sees it now
        SDL_RenderPresent(renderer);
    }
    //turns off renderer
    SDL_DestroyRenderer(renderer);
    //destroys the window
    SDL_DestroyWindow(window);
    //powers off the video initialized by SDL_Init
    SDL_Quit();
    return 0;
}
