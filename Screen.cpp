#include "Screen.h"
#include "Error.h"

Screen::Screen(const std::string& title, int width, int height)
    : title(title), width(width), height(height)
    , window(nullptr), glContext(NULL)
{
}

bool Screen::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        cleanup();
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr)
    {
        Fatal("SDL_GL context could not be created!");
    }

    int version = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    if (version == 0)
    {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }

    // Successfully loaded OpenGL
    std::cout << "OpenGL version loaded: " << GLVersion.major << "."
        << GLVersion.minor << std::endl;
    std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    int adaptiveVSyncResullt = SDL_GL_SetSwapInterval(-1);
    if (adaptiveVSyncResullt == -1)
    {
        // Set to VSync if adaptive vsync is not working
        std::cout << "could not use adaptive vsync" << std::endl;
        SDL_GL_SetSwapInterval(1);
    }

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Screen::cleanup()
{
    if (glContext != NULL)
    {
        SDL_GL_DeleteContext(glContext);
        glContext = NULL;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

Screen::~Screen()
{
    cleanup();
}