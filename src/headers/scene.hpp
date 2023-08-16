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
    Sound eatSound;
    Sound hitSound;

public:
    Snake *snake;
    Food *food;

    int score;

    Scene(/* args */);
    ~Scene();

    void Update();
    void Draw();
    void GameOver();

    bool IsValidFoodPos();
};

Scene::Scene()
{
    snake = new Snake();
    food = new Food();
    score = 0;

    InitAudioDevice();
    eatSound = LoadSound("sounds/eat.mp3");
    hitSound = LoadSound("sounds/hit.mp3");
}

Scene::~Scene()
{
    delete snake;
    delete food;

    UnloadSound(eatSound);
    UnloadSound(hitSound);
    CloseAudioDevice();
}

void Scene::Update()
{
    if (!snake->IsInScene())
        GameOver();
    if (snake->HasHitTail())
        GameOver();
    
    snake->Update();

    if (Vector2Equals(snake->body[0], food->pos))
    {
        score++;
        // Render out of the screen, will be added the next frame (gives growing effect)
        snake->body.push_back(Vector2{-1, -1});

        PlaySound(eatSound);
        // Check whether the food placement is valid
        int n = 0;
        while (!IsValidFoodPos())
            food->GenerateRandomPos();
    }
}

void Scene::Draw()
{
    snake->Draw();
    food->Draw();
}

void Scene::GameOver()
{
    PlaySound(hitSound);
    
    snake->dir = STOP;
    score = 0;

    delete snake;
    snake = new Snake();

    food->GenerateRandomPos();
}

bool Scene::IsValidFoodPos()
{
    for (int i = 0; i<snake->body.size(); i++)
    {
        if(Vector2Equals(snake->body[i], food->pos))
            return false;
    }
    return true;
}

#endif