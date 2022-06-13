/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: Juseung Yang
Creation date: 3/25/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine/Sprite.h"
#include "..\Engine/Input.h"
#include "..\Engine/Vec2.h"
#include "..\Engine\TransformMatrix.h"

class Ship {
public:
    Ship(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw();

private:
    CS230::Sprite sprite;
    CS230::Sprite flameLeft;
    CS230::Sprite flameRight;
    math::vec2 startPos;
    math::vec2 position;

    CS230::InputKey rotateCounterKey;
    CS230::InputKey rotateClockKey;
    CS230::InputKey accelerateKey;

    void TestForWrap();

    math::vec2 velocity;
    static constexpr double accel = 400;
    static constexpr double drag = 1.0f;
    double currentRotation = 0;
    static constexpr double speed = 10;

    math::TransformMatrix objectMatrix;
};
