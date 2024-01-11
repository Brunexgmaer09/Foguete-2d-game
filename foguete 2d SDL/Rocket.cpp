#include "Rocket.h"
#include <cmath>
#include <SDL_image.h>

Rocket::Rocket(SDL_Renderer* rend) : renderer(rend), posX(960.0f), posY(540.0f), angle(0.0f), velX(0.0f), velY(0.0f), aceleracao(0.5f), gravidade(0.3f), acelerando(false) {
    loadTextures();
}

Rocket::~Rocket() {
    freeTextures();
}

void Rocket::loadTextures() {
    SDL_Surface* tempSurface = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\fundo.png");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\coleta.png");
    collectionTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    collectionWidth = tempSurface->w; 
    collectionHeight = tempSurface->h; 
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\navio.png");
    shipTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    shipWidth = tempSurface->w; 
    shipHeight = tempSurface->h; 
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\foguete.png");
    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("C:\\Users\\bruno\\source\\repos\\Project1\\Debug\\foguete_acelerando.png");
    textureAccelerating = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

void Rocket::freeTextures() {
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textureAccelerating);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(collectionTexture);
    SDL_DestroyTexture(shipTexture);
}

void Rocket::update(const Uint8* keystates) {
    if (keystates[SDL_SCANCODE_A]) {
        angle -= static_cast<float>(5.0);
    }
    if (keystates[SDL_SCANCODE_D]) {
        angle += static_cast<float>(5.0);
    }

    if (keystates[SDL_SCANCODE_SPACE]) {
        acelerando = true;
        velX += aceleracao * static_cast<float>(std::sin(angle * M_PI / 180.0));
        velY -= aceleracao * static_cast<float>(std::cos(angle * M_PI / 180.0));
    }
    else {
        acelerando = false;
        velY += gravidade;
    }

    posX += velX;
    posY += velY;

    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    if (posX > 1920 - 400) posX = 1920 - 400;
    if (posY > 1080 - 200) posY = 1080 - 200;
}

void Rocket::renderBackground() {
    SDL_Rect backgroundPos = { 0, 0, 1920, 1080 };
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundPos);

    SDL_Rect shipPos = { 860, 800, shipWidth, shipHeight }; // Use shipWidth e shipHeight
    SDL_RenderCopy(renderer, shipTexture, NULL, &shipPos);

    SDL_Rect collectionPos = { 1000, 500, collectionWidth, collectionHeight }; // Use collectionWidth e collectionHeight
    SDL_RenderCopy(renderer, collectionTexture, NULL, &collectionPos);
}

void Rocket::render() {
    SDL_Rect rocketPos = { static_cast<int>(posX), static_cast<int>(posY), 400, 200 };
    if (acelerando) {
        SDL_RenderCopyEx(renderer, textureAccelerating, NULL, &rocketPos, angle, NULL, SDL_FLIP_NONE);
    }
    else {
        SDL_RenderCopyEx(renderer, texture, NULL, &rocketPos, angle, NULL, SDL_FLIP_NONE);
    }
}
