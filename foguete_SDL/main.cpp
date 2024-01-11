#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Jogo 2D do Foguete com SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* tempSurfaceRocket = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\foguete.png");
    SDL_Surface* tempSurfaceRocketAccelerating = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\foguete_acelerando.png");
    SDL_Surface* tempSurfaceBackground = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\fundo.png");
    SDL_Surface* tempSurfaceCollectible = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\coleta.png");
    SDL_Surface* tempSurfaceShip = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\navio.png");

    SDL_Surface* tempSurfaceBackgroundScaled = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0, 0, 0, 0);
    SDL_BlitScaled(tempSurfaceBackground, NULL, tempSurfaceBackgroundScaled, NULL);

    SDL_Texture* rocketTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceRocket);
    SDL_Texture* rocketAcceleratingTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceRocketAccelerating);
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceBackgroundScaled);
    SDL_Texture* collectibleTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceCollectible);
    SDL_Texture* shipTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceShip);

    SDL_FreeSurface(tempSurfaceRocket);
    SDL_FreeSurface(tempSurfaceRocketAccelerating);
    SDL_FreeSurface(tempSurfaceBackground);
    SDL_FreeSurface(tempSurfaceBackgroundScaled);
    SDL_FreeSurface(tempSurfaceCollectible);
    SDL_FreeSurface(tempSurfaceShip);

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    float posX = 960.0f;
    float posY = 540.0f;
    int width = 400;
    int height = 200;

    float fogueteAngle = 0.0f;
    float fogueteVelX = 0.0f;
    float fogueteVelY = 0.0f;
    float aceleracao = 0.5f;
    float gravidade = 0.3f;

    bool running = true;
    SDL_Event event;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (running) {
        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        if (keystates[SDL_SCANCODE_A]) {
            fogueteAngle -= 5.0f;
        }
        if (keystates[SDL_SCANCODE_D]) {
            fogueteAngle += 5.0f;
        }

        if (keystates[SDL_SCANCODE_SPACE]) {
            fogueteVelX += aceleracao * std::sin(fogueteAngle * M_PI / 180.0f); // Impulso na direção do ângulo no eixo X
            fogueteVelY -= aceleracao * std::cos(fogueteAngle * M_PI / 180.0f); // Impulso na direção do ângulo no eixo Y
        }
        else {
            fogueteVelY += gravidade; // Aplicar gravidade apenas ao eixo Y
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }

        posX += fogueteVelX; // Atualizar posição X
        posY += fogueteVelY; // Atualizar posição Y

        if (posX < 0) posX = 0;
        if (posY < 0) posY = 0;
        if (posX > 1920 - width) posX = 1920 - width;
        if (posY > 1080 - height) posY = 1080 - height;

        SDL_Rect foguetePos = { static_cast<int>(posX), static_cast<int>(posY), width, height };
        SDL_Rect backgroundPos = { 0, 0, 1920, 1080 };
        SDL_Rect collectiblePos = { 960, 0, tempSurfaceCollectible->w, tempSurfaceCollectible->h };
        SDL_Rect shipPos = { 960, 1080 - tempSurfaceShip->h, tempSurfaceShip->w, tempSurfaceShip->h };

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundPos);
        SDL_RenderCopyEx(renderer, keystates[SDL_SCANCODE_SPACE] ? rocketAcceleratingTexture : rocketTexture, NULL, &foguetePos, fogueteAngle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopy(renderer, collectibleTexture, NULL, &collectiblePos);
        SDL_RenderCopy(renderer, shipTexture, NULL, &shipPos);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(rocketTexture);
    SDL_DestroyTexture(rocketAcceleratingTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(collectibleTexture);
    SDL_DestroyTexture(shipTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
