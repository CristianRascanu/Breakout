#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true)
{
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
    float position = _sprite.getPosition().x;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        _sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
    }
}

void Paddle::moveRight(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width)
    {
        _sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
    }
}

//Moves the paddle with the mouse.
void Paddle::moveWithMouse(float dt) {

    // Get the current mouse position relative to the window.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
	float windowWidth = static_cast<float>(_window->getSize().x);
    float paddleWidth = _width;

    // Limits the paddle to stay within the window boundaries
    if(windowWidth <= paddleWidth){
        _sprite.setPosition(0.f, _sprite.getPosition().y);
    }
    float x = static_cast<float>(mousePosition.x) - _width / 2.0f;

    // Clamp the x position to ensure the paddle stays withing the boundaries of the window
    x = std::max(0.f, std::min(x, windowWidth - paddleWidth));

    float currentX = _sprite.getPosition().x;
    float positionDifference = x - currentX;
    float movement = PADDLE_SPEED * dt;

    // Move the paddle towards the target position.
    if(std::abs(positionDifference) < movement) {
        currentX = x;
    } else {
        currentX += (positionDifference > 0 ? movement : -movement);
    }

	currentX = std::max(0.f, std::min(currentX, windowWidth - paddleWidth));

    _sprite.setPosition(currentX, _sprite.getPosition().y);
}


void Paddle::update(float dt)
{
    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }
}

void Paddle::render()
{
    _window->draw(_sprite);
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    _timeInNewSize = duration;
    float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    _sprite.setPosition(newX, _sprite.getPosition().y);
}
