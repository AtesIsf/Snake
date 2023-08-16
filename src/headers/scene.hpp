#ifndef SCENE_HPP
#define SCENE_HPP

#include <raylib.h>
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

    if (snake->body[0].x == food->pos.x && snake->body[0].y == food->pos.y)
    {
        score++;

        // Check whether the food placement is valid
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
        if(snake->body[i].x == food->pos.x && snake->body[i].y == food->pos.y)
            return false;
    }
    return true;
}

#endif