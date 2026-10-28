#include "PowerupSuperBall.h"

PowerupSuperBall::PowerupSuperBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, ball, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupSuperBall::~PowerupSuperBall()
{
}

std::pair<POWERUPS, float> PowerupSuperBall::applyEffect()
{
    _ball->SetSuperBall(5.0f);
    return { superBall, 5.0f };
}