#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

int main(void) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindow("Fluorite", 500, 500, 0);

    SDL_Delay(5000);
    return 0;
}
