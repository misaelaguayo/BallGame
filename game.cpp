#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

class Ball
{
    public:
        int x;
        int y;
	int h;
	int radius;
	int r;
	int g;
	int b;
	int a;

        Ball(int x, int y, int h, int radius, int r, int g, int b, int a){
            this->x = x;
            this->y = y;
            this->h = h;
            this->radius = radius;
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
	}
        void draw(SDL_Renderer* gRenderer){
		filledCircleRGBA(gRenderer, this->x, this->y, this->radius, this->r, this->g, this->b, this->a);
	};
        void update();
        void handleInput();

};

// Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRAVITY = 1;

// Function prototypes
bool init();
void close();
void updateBallPosition(Ball& ball, int& yVelocity);
void handleInput(Ball& ball, int& yVelocity);

// SDL-related variables
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


// Main function
int main(int argc, char* argv[])
{
    Ball ball = *new Ball(320, 240, 20, 20, 0, 0, 255, 255);
    // Initialize SDL
    if (!init())
    {
        std::cerr << "Failed to initialize SDL" << std::endl;
        return 1;
    }

    // Set up ball's initial position
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
        handleInput(ball, yVelocity);

        // Update ball position
        updateBallPosition(ball, yVelocity);

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        ball.draw(gRenderer);

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

void handleInput(Ball& ball, int& yVelocity)
{
    // Handle arrow key input
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        ball.x -= 5;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        ball.x += 5;
    }
    else if (currentKeyStates[SDL_SCANCODE_UP] && yVelocity == 0)
    {
        yVelocity = 20;
    }
}

void updateBallPosition(Ball& ball, int& yVelocity)
{
    ball.y -= yVelocity;
    yVelocity -= GRAVITY;

    // Check for collision with floor
    if (ball.y + ball.h > SCREEN_HEIGHT)
    {
        ball.y = SCREEN_HEIGHT - ball.h;
        yVelocity = 0;
    }
}

