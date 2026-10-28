#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Particle {
	sf::Vector2f position;
	sf::Vector2f velocity;
	float lifetime;
	sf::Color color;
	float maxLifetime;
	float radius;
};

class ParticleSystem {
public:
	void emit(const sf::Vector2f& position, sf::Color colour, int count, float lifetime);

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	std::vector<Particle> _particles;
};