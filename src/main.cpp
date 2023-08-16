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
    InitWindow(2 * OFFSET + CELL_SIZE * N_CELLS, 2 * OFFSET + CELL_SIZE * N_CELLS, WINDOW_TITLE);

    SetTargetFPS(TARGET_FPS);

    Scene *scene = new Scene();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Update every 200ms
        if(eventTriggered(0.2))
            scene->Update();
        
        if(IsKeyPressed(KEY_W) && scene->snake->dir != DOWN)
            scene->snake->dir = UP;
        if(IsKeyPressed(KEY_S) && scene->snake->dir != UP)
            scene->snake->dir = DOWN;
        // Going left at the start would end the game instantly
        if(IsKeyPressed(KEY_A) && scene->snake->dir != RIGHT && scene->snake->dir != STOP)
            scene->snake->dir = LEFT;
        if(IsKeyPressed(KEY_D) && scene->snake->dir != LEFT)
            scene->snake->dir = RIGHT;

        // Drawing
        ClearBackground(green);
        DrawRectangleLinesEx(
            Rectangle{(float)OFFSET-5, (float)OFFSET-5, (float)CELL_SIZE * N_CELLS + 10, (float)CELL_SIZE * N_CELLS + 10},
            5, darkGreen
        );
        DrawText("RayLib Snake", OFFSET-5, 20, 40, darkGreen);
        DrawText(TextFormat("Score: %d", scene->score), N_CELLS * CELL_SIZE - OFFSET-12, 25, 30, WHITE);

        scene->Draw();
        
        EndDrawing();
    }
    
    delete scene;

    CloseWindow();
    return 0;
}