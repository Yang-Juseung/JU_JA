/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Foothold.h
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

class Foothold {
public:
    Foothold(math::vec2 startPos);
    void Load();
    void Update(double dt, Player* player);
    void Draw(math::TransformMatrix cameraMatrix);
    math::vec2 GetPosition();
private:
    /*class State
    {
    public:
        virtual void Enter(Foothold* foothold) = 0;
        virtual void Update(Foothold* foothold, double dt) = 0;
        virtual void TestForExit(Foothold* foothold) = 0;
        virtual std::string GetName() = 0;
    };
    class State_bounce : public State
    {
    public:
        virtual void Enter(Foothold* foothold) override;
        virtual void Update(Foothold* foothold, double dt) override;
        virtual void TestForExit(Foothold* foothold) override;
        std::string GetName() override { return "Bounce"; }
    };
    class State_land : public State
    {
    public:
        virtual void Enter(Foothold* foothold) override;
        virtual void Update(Foothold* foothold, double dt) override;
        virtual void TestForExit(Foothold* foothold) override;
        std::string GetName() override { return "Land"; }
    };*/

    /*State_bounce stateBounce;
    State_land stateLand;*/

    //void ChangeState(State* newState);

    //State* currState;

    CS230::Sprite sprite;
    math::vec2 initPosition;
    math::vec2 position;
    //math::vec2 velocity;

    /*static constexpr double bounceVelocity = 750;*/

    math::TransformMatrix objectMatrix;
};
