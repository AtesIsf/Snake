#ifndef SCENE_HPP
#define SCENE_HPP

#include <raylib.h>
#include <raymath.h>
#include "consts.hpp"
#include "snake.hpp"
#include "food.hpp"

class Scene
{
private:
    /* data */
public:
    Snake *snake;
    Food *food;

    int score;

    Scene(/* args */);
    ~Scene();

    void Update();
    void Draw();
    bool IsValidPos();
};

Scene::Scene()
{
    snake = new Snake();
    food = new Food();
    score = 0;
}

Scene::~Scene()
{
    delete snake;
    delete food;
}

void Scene::Update()
{
    snake->Update();

    if (Vector2Equals(snake->body[0], food->pos))
    {
        score++;
        // Render out of the screen, will be added the next frame (gives growing effect)
        snake->body.push_back(Vector2{-1, -1});
        
        // Check whether the food placement is valid
        int n = 0;
        while (!IsValidPos())
            food->GenerateRandomPos();
    }
}

void Scene::Draw()
{
    snake->Draw();
    food->Draw();
}

bool Scene::IsValidPos()
{
    for (int i = 0; i<snake->body.size(); i++)
    {
        if(Vector2Equals(snake->body[i], food->pos))
            return false;
    }
    return true;
}

#endif