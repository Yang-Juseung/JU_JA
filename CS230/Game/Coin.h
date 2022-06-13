/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Coin.h
Project: CS230
Author: Jaeyeong An
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"
#include "Player.h"

namespace CS230
{
    class Camera;
}

class Coin {
public:
    Coin(math::vec2 startPos);
    void Load();
    void Update(double dt, Player* player);
    void Draw(math::TransformMatrix cameraMatrix);
    math::vec2 GetPosition();
    bool isCollided;
private:
    

    CS230::Sprite sprite;
    math::vec2 initPosition;
    math::vec2 position;

    math::TransformMatrix objectMatrix;

};
