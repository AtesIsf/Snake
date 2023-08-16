#include <iostream>
#include <raylib.h>

#include "headers/consts.hpp"
#include "headers/scene.hpp"

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
    double currTime = GetTime();
    if (currTime-lastUpdateTime >= interval)
    {
        lastUpdateTime = currTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(CELL_SIZE * N_CELLS, CELL_SIZE * N_CELLS, WINDOW_TITLE);

    SetTargetFPS(TARGET_FPS);

    Scene *scene = new Scene();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Drawing
        ClearBackground(green);
        
        // Update every 200ms
        if(eventTriggered(0.2))
            scene->Update();
        
        if(IsKeyPressed(KEY_W) && scene->snake->dir != DOWN)
            scene->snake->dir = UP;
        if(IsKeyPressed(KEY_S) && scene->snake->dir != UP)
            scene->snake->dir = DOWN;
        if(IsKeyPressed(KEY_A) && scene->snake->dir != RIGHT)
            scene->snake->dir = LEFT;
        if(IsKeyPressed(KEY_D) && scene->snake->dir != LEFT)
            scene->snake->dir = RIGHT;

        scene->Draw();
        
        EndDrawing();
    }
    
    delete scene;

    CloseWindow();
    return 0;
}