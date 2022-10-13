#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

class Obstacle
{
public:
    Obstacle(Texture2D spriteSheet);
    void SetPosition(int winWidth, int winHeight);
    virtual void tick(float deltaTime);
    Rectangle GetCollisionRect() {return collisionRect;};
    Vector2 GetPos() {return pos;};
    bool GetActive() {return active;};
    void SetActive(bool newActive) {active = newActive;};

protected:
    Texture2D texture{};
    Rectangle spriteRect{};
    Vector2 pos{};

    int xFrame{0}, yFrame{0};
    int maxXFrame{7};
    int maxYFrame{7};
    float updateTime{0.0};
    float runningTime{0.0};

    int speed{-200};
    float pad{50};
    Rectangle collisionRect{};
    bool  active{false};

};

#endif