#include "Background.h"

Background::Background(const char *textureFilePath, float scrollSpeed) : speed(scrollSpeed)
{
    texture = LoadTexture(textureFilePath);
}

Background::~Background()
{
    UnloadTexture(texture);
}

void Background::tick(float deltaTime)
{
    xPos -= speed * deltaTime;

    if(xPos <= -texture.width*2)
    {
        xPos = 0.0f;
    }

    DrawTextureEx(texture, {xPos, 0.0}, 0.0, 2.0, WHITE);
    DrawTextureEx(texture, {xPos + texture.width * 2, 0.0}, 0.0, 2.0, WHITE);
}