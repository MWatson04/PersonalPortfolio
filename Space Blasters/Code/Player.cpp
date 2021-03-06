#include "Player.h"


// Private Functions
void Player::InitializeVariables()
{
	movementSpeed = 20.f;
	attackCooldown = 3.f;
	timeSinceLastAttack = attackCooldown;
	points = 0;
	maxHealth = 10;
	currentHealth = maxHealth;
}

void Player::InitializePlayerTexture()
{
	// Get texture for player
	if (!playerTexture.loadFromFile("Textures/ship.png"))
		std::cout << "ERROR::PLAYER::SHIP.PNG COULD NOT LOAD!" << std::endl;
}

void Player::InitializePlayerSprite()
{
	// Assign the texture to the sprite
	playerSprite.setTexture(playerTexture);
	playerSprite.scale(0.08f, 0.08f);
	playerSprite.setPosition(355.f, 450.f);
}

// Constructor & Destructor
Player::Player()
{
	InitializeVariables();
	InitializePlayerTexture();
	InitializePlayerSprite();
}

Player::~Player()
{

}

// Getters
const sf::Vector2f& Player::GetPosition() const
{
	return playerSprite.getPosition();
}

const sf::FloatRect Player::GetGlobalBounds() const
{
	return playerSprite.getGlobalBounds();
}

const int Player::GetCurrentHealth() const
{
	return currentHealth;
}

// Setters
const int& Player::SetPoints(int added_Points)
{
	return points += added_Points;
}

const int& Player::SetCurrentHealth(int health_Damage)
{
	if (currentHealth < 0)
		currentHealth = 0;
	if (currentHealth > maxHealth)
		currentHealth = maxHealth;

	currentHealth += health_Damage;

	return currentHealth;
}

// Public Functions
void Player::MovePlayer(const float dirX, const float dirY)
{
	playerSprite.move(movementSpeed * dirX, movementSpeed * dirY);
}

const bool Player::CanAttack()
{
	// Cooldown for shooting
	if (timeSinceLastAttack >= attackCooldown)
	{
		timeSinceLastAttack = 0.f;
		return true;
	}
	
	return false;
}

void Player::UpdatePlayerWindowCollisions(const sf::RenderTarget* target)
{
	// Set players movement boundaries to window size
	// Left
	if (playerSprite.getPosition().x <= 0.f)
		playerSprite.setPosition(0.f, playerSprite.getPosition().y);
	// Right
	if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width >= target->getSize().x)
		playerSprite.setPosition(target->getSize().x - playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
	// Top
	if (playerSprite.getPosition().y <= 0.f)
		playerSprite.setPosition(playerSprite.getPosition().x, 0.f);
	// Bottom
	if (playerSprite.getPosition().y + playerSprite.getGlobalBounds().height >= target->getSize().y)
		playerSprite.setPosition(playerSprite.getPosition().x, target->getSize().y - playerSprite.getGlobalBounds().height);
}

void Player::UpdateAttackCooldown()
{
	// Increase attack timer
	if (timeSinceLastAttack < attackCooldown)
		timeSinceLastAttack += 0.5f;
}

void Player::Update()
{
	UpdateAttackCooldown();
}

void Player::Render(sf::RenderTarget* target)
{
	// Draw player sprite
	target->draw(playerSprite);
}
