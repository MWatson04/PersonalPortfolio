#pragma once

#include <SFML/Graphics.hpp>


class HealthPack
{
private:
	sf::Sprite healthPackSprite;

public:
	// Constructor & Destructor
	HealthPack();
	HealthPack(sf::Texture* health_Pack_Texture, float pos_X, float pos_Y);
	~HealthPack();

	// Getters
	const sf::FloatRect GetGlobalBounds() const;
	const sf::Vector2f& GetPosition() const;

	// Setters
	void SetPosition(float pos_X, float pos_Y);

	// Public Functions
	void Update();
	void Render(sf::RenderTarget* target);
};

