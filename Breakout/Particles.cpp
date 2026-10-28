#include "Particles.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

void ParticleSystem::emit(const sf::Vector2f& position, sf::Color colour, int count, float lifetime) {
	for (int i = 0; i < count; ++i) {
		const float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f;

		const float speed = 40.0f + static_cast<float>(std::rand() % 120);

		Particle p;
		p.position = position;
		p.velocity = { std::cos(angle) * speed, std::sin(angle) * speed };
		p.color = colour;
		p.lifetime = lifetime;
		p.maxLifetime = lifetime;
		p.radius = 2.0f + static_cast<float>(std::rand() % 3); // Random radius between 2 and 4
		_particles.push_back(p);
	}
}

void ParticleSystem::update(float deltaTime) {
	for (auto& p : _particles) {
		p.position += p.velocity * deltaTime;
		p.lifetime -= deltaTime;
	}

	// Remove dead particles
	_particles.erase(std::remove_if(_particles.begin(), _particles.end(),
		[](const Particle& p) { return p.lifetime <= 0; }), _particles.end());
}	

void ParticleSystem::draw(sf::RenderWindow& window) {
	for (const auto& p : _particles) {
		sf::CircleShape shape(p.radius);
		shape.setOrigin(p.radius, p.radius);
		shape.setPosition(p.position);

		float alpha = p.lifetime / p.maxLifetime;
		alpha = std::max(0.0f, std::min(1.0f, alpha));

		sf::Color colour = p.color;
		colour.a = static_cast<sf::Uint8>(colour.a * alpha);

		shape.setFillColor(colour);
		window.draw(shape);
	}
}