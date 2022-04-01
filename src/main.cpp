#include <iostream>
#include <SDL2/SDL.h>
#include "Input.hpp"
#include "Time.hpp"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
#define WINDOW_TITLE "SDL2 DEMO"

void setWindowTitle(SDL_Window* window);

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to init: %s", SDL_GetError());

        return EXIT_FAILURE;
    } 

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if(window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create window: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create renderer: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    bool running = true;

    while(running)
    {
        running = Input::Instance()->Listen();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        SDL_RenderClear(renderer);

        setWindowTitle(window);

        SDL_RenderPresent(renderer);
    }
   
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

void setWindowTitle(SDL_Window* window)
{
    std::string title = std::string(WINDOW_TITLE);
    title += " | ";

    Time* time = new Time();
    title += std::string(time->String());
    title += " | ";
    delete time;

    SDL_Point cursor = Input::Instance()->GetCursor();
    title += "MX=" + std::to_string(cursor.x);
    title += " | ";
    title += "MY=" + std::to_string(cursor.y);

   SDL_SetWindowTitle(window, title.c_str()); 
}
