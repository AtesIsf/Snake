#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <raylib.h>
#include <vector>
#include "consts.hpp"

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
};

class Snake
{
    private:
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();

    public:
        Direction dir;
        std::vector<Vector2> body = std::vector<Vector2>();

        Snake();
        ~Snake();
        void Draw();
        void Update();

        bool IsInScene();
        bool HasHitTail();
};

Snake::Snake()
{
    body.push_back(Vector2{6, 9});
    body.push_back(Vector2{7, 9});
    dir = STOP;
}

Snake::~Snake()
{
}

void Snake::Draw()
{
    for (int i = 0; i<body.size(); i++)
        if (body[i].x < N_CELLS && body[i].x > -1 && body[i].y < N_CELLS && body[i].y > -1)
            DrawRectangleRounded(
                Rectangle{OFFSET + (float)body[i].x * CELL_SIZE, OFFSET + (float)body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 
                0.5, 6, darkGreen
            );
}

void Snake::Update()
{
    if(dir == UP)
        MoveUp();
    if(dir == DOWN)
        MoveDown();
    if(dir == LEFT)
        MoveLeft();
    if(dir == RIGHT)
        MoveRight();
}

void Snake::MoveUp()
{
    // Copy all elements' coordinates to match the previous
    for (int i = body.size()-1; i>0; i--)
    {
        body[i].x = body[i-1].x;
        body[i].y = body[i-1].y;
    }
    
    // Update the head
    body[0].y--;
}

void Snake::MoveDown()
{
    // Copy all elements' coordinates to match the previous
    for (int i = body.size()-1; i>0; i--)
    {
        body[i].x = body[i-1].x;
        body[i].y = body[i-1].y;
    }

    // Update the head
    body[0].y++; 
}

void Snake::MoveLeft()
{
    // Copy all elements' coordinates to match the previous
    for (int i = body.size()-1; i>0; i--)
    {
        body[i].x = body[i-1].x;
        body[i].y = body[i-1].y;
    }
    
    // Update the head
    body[0].x--;   
}

void Snake::MoveRight()
{
    // Copy all elements' coordinates to match the previous
    for (int i = body.size()-1; i>0; i--)
    {
        body[i].x = body[i-1].x;
        body[i].y = body[i-1].y;
    }
    
    // Update the head
    body[0].x++;
}

bool Snake::IsInScene()
{
    if (body[0].x >= N_CELLS || body[0].x <= 0 || 
        body[0].y >= N_CELLS || body[0].y <= 0)
        return false;
    return true;
}

bool Snake::HasHitTail()
{
    for (int i = 1; i<body.size(); i++)
        if (Vector2Equals(body[0], body[i]))
            return true;
    return false;
}

#endif