#pragma once
#include "PowerupBase.h"

class PowerupMagnetPaddle : public PowerupBase
{
public:
    PowerupMagnetPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x);
	~PowerupMagnetPaddle();

	std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};

