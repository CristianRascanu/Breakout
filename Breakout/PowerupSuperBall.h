#pragma once

#include "PowerupBase.h"

class PowerupSuperBall : public PowerupBase
{
public:
    PowerupSuperBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos);
    ~PowerupSuperBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
#pragma once
