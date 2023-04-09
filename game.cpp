#include <SDL2/SDL.h>
#include <iostream>

// Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BALL_SIZE = 40;
const int GRAVITY = 1;

// Function prototypes
bool init();
void close();
void updateBallPosition(SDL_Rect& ballRect, int& yVelocity);
void handleInput(SDL_Rect& ballRect, int& yVelocity);

// SDL-related variables
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

// Main function
int main(int argc, char* argv[])
{
    // Initialize SDL
    if (!init())
    {
        std::cerr << "Failed to initialize SDL" << std::endl;
        return 1;
    }

    // Set up ball's initial position
    SDL_Rect ballRect = {SCREEN_WIDTH/2 - BALL_SIZE/2, SCREEN_HEIGHT - BALL_SIZE, BALL_SIZE, BALL_SIZE};
    int yVelocity = 0;

    // Game loop
    bool quit = false;
    while (!quit)
    {
        // Handle events
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Handle input
        handleInput(ballRect, yVelocity);

        // Update ball position
        updateBallPosition(ballRect, yVelocity);

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Draw ball
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &ballRect);

        // Update screen
        SDL_RenderPresent(gRenderer);
    }

    // Clean up and exit
    close();
    return 0;
}

bool init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    gWindow = SDL_CreateWindow("Ball Jumping Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close()
{
    // Destroy renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

void handleInput(SDL_Rect& ballRect, int& yVelocity)
{
    // Handle arrow key input
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        ballRect.x -= 5;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        ballRect.x += 5;
    }
    else if (currentKeyStates[SDL_SCANCODE_UP] && yVelocity == 0)
    {
        yVelocity = 20;
    }
}

void updateBallPosition(SDL_Rect& ballRect, int& yVelocity)
{
    ballRect.y -= yVelocity;
    yVelocity -= GRAVITY;

    // Check for collision with floor
    if (ballRect.y + ballRect.h > SCREEN_HEIGHT)
    {
        ballRect.y = SCREEN_HEIGHT - ballRect.h;
        yVelocity = 0;
    }
}

