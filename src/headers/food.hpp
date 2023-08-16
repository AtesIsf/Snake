#ifndef FOOD_HPP
#define FOOD_HPP

#include <raylib.h>
#include "consts.hpp"

class Food
{
    private:
        Texture2D texture;

    public:
        // Cells, not pixels!!!
        Vector2 pos;

        Food();
        ~Food();
        void Draw();
        void GenerateRandomPos();
};

Food::Food()
{
    GenerateRandomPos();

    Image foodImg = LoadImage("img/food.png");
    texture = LoadTextureFromImage(foodImg);
    UnloadImage(foodImg);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    // Multiply by CELL_SIZE as the function takes pixels, not grid coordinates, 
    // RED is tint (white does nothing)
    DrawTexture(texture, OFFSET + pos.x * CELL_SIZE, OFFSET + pos.y * CELL_SIZE, WHITE);
}

void Food::GenerateRandomPos()
{
    pos.x = GetRandomValue(0, N_CELLS-1);
    pos.y = GetRandomValue(0, N_CELLS-1);
}

#endif