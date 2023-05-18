#pragma once
#include <list>
#include "settings.h"
#include "laser.h"
#include "textObj.h"
class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedY;
	void controlPlayer();
	std::list<Laser*> laserSprites;
	sf::Clock timer;
	int curTimeFire, prevTimeFire;
	int hp;
	Textobj hpText;

	void createOneLaserBlue();
	void createOneLaserGreen();
	void createOneLaserRed();
public:
	Player();

	void fire();

	void update();

	void draw(sf::RenderWindow& window);

	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }

	std::list<Laser*>* getLaserSprites() { return &laserSprites; }
};

Player::Player() : hpText(std::to_string(hp), sf::Vector2f{ 0.f,0.f }, FONT_SIZE) {
	texture.loadFromFile(PLAYER_FILENAME);
	sprite.setTexture(texture);
	sprite.setPosition(START_POS);
	timer.restart();
	prevTimeFire = timer.getElapsedTime().asMilliseconds();
}

void Player::controlPlayer() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		speedY = -SPEED_Y;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		speedY = SPEED_Y;
	}
	if (sprite.getPosition().y < 0) {
		sprite.setPosition(sprite.getPosition().x, 0.f);
	}
	else if (sprite.getPosition().y > WINDOW_HEIGHT - sprite.getGlobalBounds().height) {
		sprite.setPosition(sprite.getPosition().x, WINDOW_HEIGHT - sprite.getGlobalBounds().height);
	}
};
void Player::fire() {
	curTimeFire = timer.getElapsedTime().asMilliseconds();
	if (curTimeFire - prevTimeFire > FIRE_COOLDOWN) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			createOneLaserBlue();
			prevTimeFire = curTimeFire;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
			createOneLaserGreen();
			prevTimeFire = curTimeFire;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			createOneLaserRed();
			prevTimeFire = curTimeFire;
		}
	}
}
void Player::createOneLaserBlue() {
	sf::Vector2f pos = sprite.getPosition();
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sf::Vector2f posCenter = sf::Vector2f{ pos.x + bounds.width / 2,pos.y + bounds.height / 2 };
	auto laser = new Laser(Laser::LaserType::BLUE, posCenter);
	laserSprites.push_back(laser);
}
void Player::createOneLaserRed() {
	sf::Vector2f pos = sprite.getPosition();
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sf::Vector2f posCenter = sf::Vector2f{ pos.x + bounds.width / 2,pos.y + bounds.height / 2 };
	auto laser = new Laser(Laser::LaserType::RED, posCenter);
	laserSprites.push_back(laser);
}
void Player::createOneLaserGreen() {
	sf::Vector2f pos = sprite.getPosition();
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sf::Vector2f posCenter = sf::Vector2f{ pos.x + bounds.width / 2,pos.y + bounds.height / 2 };
	auto laser = new Laser(Laser::LaserType::GREEN, posCenter);
	laserSprites.push_back(laser);
}

void Player::update() {
	speedY = 0.f;
	controlPlayer();
	sprite.move(0.f, speedY);
	fire();
	for (auto laser : laserSprites) {
		laser->update();
	}
}

void Player::draw(sf::RenderWindow& window) {
	for (auto laser : laserSprites) {
		window.draw(laser->getSprite());
	}
	window.draw(sprite);
}