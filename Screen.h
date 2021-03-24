#pragma once

#include <SDL/SDL.h>
#include <string>

class Screen
{
public:
    Screen(std::string title, int width, int height);

    ~Screen();

    bool init();

    void cleanup();

    inline SDL_Renderer* getRenderer()
    {
        return renderer;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    std::string title;
};