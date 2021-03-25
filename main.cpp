#include <iostream>

#include "Screen.h"

int main(int argc, char** argv)
{
	auto screen = new Screen("Tiling with Geometry", 1024, 768);
	screen->Init();

    bool quit = false;
    SDL_Event e;
    Uint32 lastTick = SDL_GetTicks();
    int deltaTime = 16;
    while (!quit)
    {
        Uint32 startTick = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            inputServiceManager->handleInput(&e);
        }

        while ((lastTick - deltaTime) < startTick)
        {
            updateServiceManager->update(deltaTime);

            lastTick += deltaTime;
        }

        SDL_SetRenderDrawColor(screen->getRenderer(), 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(screen->getRenderer());

        renderServiceManager->render(camera);

        SDL_RenderPresent(screen->getRenderer());
    }

}
