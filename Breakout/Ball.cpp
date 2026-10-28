#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;   // reset speed.
        else
        {
            setFireBall(0);    // disable fireball
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }
    if (_superBallTimer > 0.0f)
    {
        _superBallTimer -= dt;

    }
    else {
		if (_velocity != VELOCITY)
			_velocity = VELOCITY;   // reset speed.
		else
		{
			SetSuperBall(0.0f);    // disable superball
			_sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
		}
    }

	if (_isCaughtByPaddle)
	{
        auto paddleBounds = _gameManager->getPaddle()->getBounds();
        _sprite.setPosition(paddleBounds.left + paddleBounds.width / 2.0f - RADIUS, paddleBounds.top - 2.0f * RADIUS);

		_magnetTimer -= dt;
		if (_magnetTimer <= 0.0f)
		{
			setMagnetPaddle(0.0f); // Disable magnet effect
		}
	}

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    _trailTimer -= dt;

    if (_trailTimer <= 0.0f) {
        _gameManager->getParticleSystem().emit(_sprite.getPosition(), ballEffectsColour, 2, ballTrailLifetime);
        _trailTimer = 0.025f;
    }
        
    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        _sprite.setPosition(0, 300);
        _direction = { 1, 1 };
        _gameManager->loseLife();
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        if (_isMagnetActive) {
            _isCaughtByPaddle = true;
            return;
        }
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
		_gameManager->getParticleSystem().emit(_sprite.getPosition(), paddleEffectsColour, 10, paddleBurstLifetime);
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall || _isSuperBall) return; // no collisisons when in fireBall mode.

    if (_isSuperBall) {
        _superBallTimer -= dt;
		if (_superBallTimer <= 0.0f) {
			SetSuperBall(0.0f); // Disable super ball effect
		}
    }

    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
    }
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY;
    _timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration;        
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;    
}

void Ball::SetSuperBall(float duration)
{
    if (duration)
    {
        _isSuperBall = true;
        _superBallTimer = duration;
        return;
    }
    _isSuperBall = false;
    _superBallTimer = 0.0f;
}

void Ball::setMagnetPaddle(float duration)
{
    if (duration)
    {
        _isMagnetActive = true;
        _magnetTimer = duration;
        return;
    }
    _isMagnetActive = false;
    _magnetTimer = 0.0f;
}
void Ball::launchFromPaddle()
{
	if (_isCaughtByPaddle)
	{
		_isCaughtByPaddle = false;
		_direction = { 1, -1 }; // Launch upwards
	}
}