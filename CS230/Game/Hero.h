/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Juseung Yang
Creation date: 3/25/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine/Sprite.h"
#include "..\Engine/Input.h"
#include "..\Engine/Vec2.h"
#include "..\Engine\TransformMatrix.h"

namespace CS230 
{
    class Camera;
}

class Hero {
public:
    Hero(math::vec2 startPos, const CS230::Camera& camera);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix cameraMatrix);
    math::vec2 GetPosition();

    class State
    {
    public:
        virtual void Enter(Hero* hero) = 0;
        virtual void Update(Hero* hero, double dt) = 0;
        virtual void TestForExit(Hero* hero) = 0;
        virtual std::string GetName() = 0;
    };
    class State_Idle : public State
    {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public State
    {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Skidding : public State
    {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Skidding"; }
    };
    class State_Jumping : public State
    {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Falling : public State
    {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Falling"; }
    };

    void ChangeState(State* newState);

    State* currState;

    State_Idle stateIdle;
    State_Running stateRunning;
    State_Skidding stateSkidding;
    State_Jumping stateJumping;
    State_Falling stateFalling;

private:


    void UpdateXVelocity(double dt);     //Change X velocity stuff


    CS230::Sprite sprite;
    math::vec2 startPos;
    math::vec2 position;

    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey moveUpKey;


    math::vec2 velocity;
    static constexpr double jumpVelocity = 1000;
    static constexpr double Xacceleration = 800;
    static constexpr double Xdrag = 1000;
    static constexpr double Xmaxvelocity = 1000;
    bool isJumping;
    bool isRising;
    bool isFlipping;

    const CS230::Camera& camera;

    math::TransformMatrix objectMatrix;

    double health{ 3 };
};
