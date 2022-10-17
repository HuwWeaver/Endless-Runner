#include "raylib.h"
#include "Background.h"
#include "Obstacle.h"
#include "Character.h"
#include <string>

int main ()
{
    //Window Dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 358;

    InitWindow(windowDimensions[0], windowDimensions[1], "Endless Runner");

    //Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    const int sizeOfNebulae{5};

    Obstacle nebulaePool[sizeOfNebulae]{
        Obstacle{nebula},
        Obstacle{nebula},
        Obstacle{nebula},
        Obstacle{nebula},
        Obstacle{nebula}
    };

    for(int i =0; i < sizeOfNebulae; i++)
    {
        nebulaePool[i].SetInitialPosition(windowDimensions[0], windowDimensions[1]);
    }
    
    //Scarfy variables
    Character scarfy{windowDimensions[0], windowDimensions[1]};

    //Nebula collision
    bool gameOver{};
    
    //Backgrounds
    Background background{"textures/far-buildings.png", 20};
    Background midground{"textures/back-buildings.png", 40};
    Background foreground{"textures/foreground.png", 80};

    //obstacle timer
    float runningTime{2.0};
    float obstacleInterval{2.0};
    float score{0};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //get delta time
        const float dt{GetFrameTime()};
        
        BeginDrawing();
        ClearBackground(WHITE);

        //Scroll paralax backgrounds
        background.tick(dt);
        midground.tick(dt);
        foreground.tick(dt);

        if(gameOver)
        {
            //Lose the game
            DrawText("Game Over!", windowDimensions[0]/4, windowDimensions[1]/2, 50, WHITE);

            //Draw Score
            std::string scoreText = "Score: ";
            scoreText.append(std::to_string(score), 0, 5);
            DrawText(scoreText.c_str(), 5, 5, 25, WHITE);
        }
        else
        {
            score += dt;
            runningTime += dt;
            if(runningTime >= obstacleInterval)
            {
                runningTime = 0;
                obstacleInterval -= dt; //reduce interval between obstacles - could do with refinement

                //find inactive obstacle in pool
                for (int i=0; i < sizeOfNebulae; i++)
                {
                    if(!nebulaePool[i].GetActive())
                    {
                        //Spawn inactive obstacle and stop searching
                        nebulaePool[i].SetActive(true);
                        nebulaePool[i].SetInitialPosition(windowDimensions[0], windowDimensions[1]);
                        break;
                    }
                }
            }
            
            //tick all active nebula obstacles - update animation, position, and collisions
            for (int i=0; i < sizeOfNebulae; i++)
            {
                if(nebulaePool[i].GetActive()) nebulaePool[i].tick(dt);            
            } 

            //tick character
            scarfy.tick(dt, windowDimensions[1]);

            //Check obstacle collisions
            for (Obstacle obstacle : nebulaePool)
            {          
                if(CheckCollisionRecs(obstacle.GetCollisionRect(), scarfy.GetCollisionRect()))
                {
                    gameOver = true;
                }
            }

            //Draw Score
            std::string scoreText = "Score: ";
            scoreText.append(std::to_string(score), 0, 5);
            DrawText(scoreText.c_str(), 5, 5, 25, WHITE);
        }

        EndDrawing();
    }

    //Unload all textures
    UnloadTexture(nebula);

    CloseWindow();
}