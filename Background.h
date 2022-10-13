#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "raylib.h"

class Background
{
public:
    Background(const char *textureFilePath, float scrollSpeed);
    ~Background();
    virtual void tick(float deltaTime);

protected:
    Texture2D texture{};
    float xPos{}, speed{};
};

#endif