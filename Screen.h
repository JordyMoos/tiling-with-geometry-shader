#pragma once

#include <glad/glad.h>
#include <SDL/SDL.h>
#include <string>

class Screen
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    std::string title;

public:

    Screen(const std::string& title, int width, int height);

    ~Screen();

    bool Init();

    inline SDL_Renderer* GetRenderer()
    {
        return renderer;
    }

    int GetWidth() const
    {
        return width;
    }

    int GetHeight() const
    {
        return height;
    }

private:

    void cleanup();
};