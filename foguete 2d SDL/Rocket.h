#pragma once
#ifndef ROCKET_H
#define ROCKET_H

#include <SDL.h>

class Rocket {
public:
    Rocket(SDL_Renderer* renderer);
    ~Rocket();

    void update(const Uint8* keystates);
    void render();
    void renderBackground();

private:
    float posX, posY;
    float angle;
    float velX, velY;
    float aceleracao;
    float gravidade;
    bool acelerando;
    int shipWidth, shipHeight;
    int collectionWidth, collectionHeight;


    SDL_Texture* texture;
    SDL_Texture* textureAccelerating;
    SDL_Texture* backgroundTexture;
    SDL_Texture* collectionTexture;
    SDL_Texture* shipTexture;

    SDL_Renderer* renderer;

    void loadTextures();
    void freeTextures();
};

#endif