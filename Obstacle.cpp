#include "Obstacle.h"

Obstacle::Obstacle(Texture2D spriteSheet)
{
    texture = spriteSheet;
    spriteRect = {0, 0, static_cast<float>(texture.width/8), static_cast<float>(texture.height/8)};
}

void Obstacle::SetPosition(int winWidth, int winHeight)
{
    pos = {static_cast<float>(winWidth + 200), static_cast<float>(winHeight - texture.height/8)};
}

void Obstacle::tick(float deltaTime)
{
    pos.x += speed * deltaTime;
    if(pos.x <= -100) SetActive(false);

    //Update running time
    runningTime += deltaTime;
    if(runningTime >= updateTime)
    {
        runningTime = 0.0;
        //Update animation frame
        spriteRect.x = xFrame * spriteRect.width;
        spriteRect.y = yFrame * spriteRect.height;

        xFrame++;
        if(xFrame > maxXFrame)
        {
            xFrame = 0;

            yFrame++;
            if(yFrame > maxYFrame)
            {
                yFrame = 0;
            }
        }

        if(yFrame == maxYFrame && xFrame > 4)
        {
            xFrame = 0;
            yFrame = 0;
        }
    }

    collisionRect = {pos.x + pad, pos.y + pad, spriteRect.width - 2*pad, spriteRect.height - 2*pad};
    DrawTextureRec(texture, spriteRect, pos, WHITE);
}