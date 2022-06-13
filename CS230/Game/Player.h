#pragma once
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.h
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

class Player {
public:
    Player(math::vec2 startPos, const CS230::Camera& camera);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix cameraMatrix);
    math::vec2 GetPosition();
    void SetHealth(double hp) { health = hp; }
    double GetHealth() { return health; };
private:
    class State
    {
    public:
        virtual void Enter(Player* Player) = 0;
        virtual void Update(Player* Player, double dt) = 0;
        virtual void TestForExit(Player* Player) = 0;
        virtual std::string GetName() = 0;
    };
    class State_Idle : public State
    {
    public:
        virtual void Enter(Player* Player) override;
        virtual void Update(Player* Player, double dt) override;
        virtual void TestForExit(Player* Player) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public State
    {
    public:
        virtual void Enter(Player* Player) override;
        virtual void Update(Player* Player, double dt) override;
        virtual void TestForExit(Player* Player) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Skidding : public State
    {
    public:
        virtual void Enter(Player* Player) override;
        virtual void Update(Player* Player, double dt) override;
        virtual void TestForExit(Player* Player) override;
        std::string GetName() override { return "Skidding"; }
    };
    class State_Jumping : public State
    {
    public:
        virtual void Enter(Player* Player) override;
        virtual void Update(Player* Player, double dt) override;
        virtual void TestForExit(Player* Player) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Falling : public State
    {
    public:
        virtual void Enter(Player* Player) override;
        virtual void Update(Player* Player, double dt) override;
        virtual void TestForExit(Player* Player) override;
        std::string GetName() override { return "Falling"; }
    };

    State_Idle stateIdle;
    State_Running stateRunning;
    State_Skidding stateSkidding;
    State_Jumping stateJumping;
    State_Falling stateFalling;

    void UpdateXVelocity(double dt);     //Change X velocity stuff
    void ChangeState(State* newState);

    State* currState;

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
