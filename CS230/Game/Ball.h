/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Juseung Yang
Creation date: 3/29/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"

namespace CS230
{
    class Camera;
}

class Ball {
public:
    Ball(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix cameraMatrix);
private:
    class State
    {
    public:
        virtual void Enter(Ball* ball) = 0;
        virtual void Update(Ball* ball, double dt) = 0;
        virtual void TestForExit(Ball* ball) = 0;
        virtual std::string GetName() = 0;
    };
    class State_bounce : public State
    {
    public:
        virtual void Enter(Ball* hero) override;
        virtual void Update(Ball* hero, double dt) override;
        virtual void TestForExit(Ball* hero) override;
        std::string GetName() override { return "Bounce"; }
    };
    class State_land : public State
    {
    public:
        virtual void Enter(Ball* hero) override;
        virtual void Update(Ball* hero, double dt) override;
        virtual void TestForExit(Ball* hero) override;
        std::string GetName() override { return "Land"; }
    };

    State_bounce stateBounce;
    State_land stateLand;

    void ChangeState(State* newState);

    State* currState;

    CS230::Sprite sprite;
    math::vec2 initPosition;
    math::vec2 position;
    math::vec2 velocity;

    static constexpr double bounceVelocity = 750 ;

    math::TransformMatrix objectMatrix;
};
