#include "Character.h"

Character::Character(int winWidth, int winHeight)
{
    texture = LoadTexture("textures/scarfy.png");
    spriteRect = {0, 0, texture.width/6.0f, texture.height/1.0f};
    pos = {winWidth/2 - (texture.width/6.0f)/2.0f, winHeight - texture.height/1.0f};
}

Character::~Character()
{
    UnloadTexture(texture);
}

bool Character::IsOnGround(int winHeight)
{
    return pos.y >= winHeight - spriteRect.height;
}

void Character::tick(float deltaTime, int winHeight)
{
    if (IsOnGround(winHeight))
    {
        //Rectangle on the floor
        scarfyVel = 0;
        isInAir = false;
    }
    else
    {
        //Rectangle in the air - Apply Gravity
        scarfyVel += gravity * deltaTime;
        isInAir = true;
    }

    if(IsKeyPressed(KEY_SPACE) && !isInAir)
    {
        scarfyVel += jumpVel;
    }

    pos.y += scarfyVel * deltaTime;

    if(!isInAir)
    {
        //Update running time
        runningTime += deltaTime;
        if(runningTime >= updateTime)
        {
            runningTime = 0.0;
            //Update animation frame
            spriteRect.x = frame * spriteRect.width;
            frame++;
            if(frame > maxFrame)
            {
                frame = 0;
            }
        }
    }

    collisionRect = {pos.x, pos.y, spriteRect.width, spriteRect.height};
    
    DrawTextureRec(texture, spriteRect, pos, WHITE);
}