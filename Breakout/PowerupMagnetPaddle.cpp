#include "PowerupMagnetPaddle.h"

PowerupMagnetPaddle::PowerupMagnetPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, ball, x_pos)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupMagnetPaddle::~PowerupMagnetPaddle()
{
}

std::pair<POWERUPS, float> PowerupMagnetPaddle::applyEffect()
{
    _ball->setMagnetPaddle(5.0f);
    return { magnetPaddle, 5.0f };
}