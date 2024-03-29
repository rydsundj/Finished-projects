//
// Created by rydsundj on 2023-12-01.
//

#include "Player.h"
#include <iostream>

Player::Player(const sf::Vector2u& windowSize) : Character(3), leftPressed(false), rightPressed(false), windowWidth(windowSize.x)
{
    if (!texture.loadFromFile("../images/farmer1.png"))
    {
        std::cerr << "Failed to load image" << std::endl;
    }
    sprite.setTexture(texture);
    this->sprite.setScale(0.15f, 0.15f);
    this->sprite.setPosition((windowSize.x / 2) - ((texture.getSize().x * 0.15) / 2), windowSize.y - 175);
}

void Player::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Left: leftPressed = true; break;
            case sf::Keyboard::Right: rightPressed = true; break;
            default: break;
        }
    } else if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::Left: leftPressed = false; break;
            case sf::Keyboard::Right: rightPressed = false; break;
            default: break;
        }
    }
}

sf::Sprite Player::getSprite() const
{
    return sprite;
}

void Player::update(const sf::Time& delta)
{
    if (leftPressed)
    {
        moveObject(-speed * delta.asSeconds(), 0);
    }

    if (rightPressed)
    {
        moveObject(speed * delta.asSeconds(), 0);
    }
}

void Player::handleCollision(std::vector<Object*>& objects, Score& score)
{
    float leftLimit = -(texture.getSize().x * 0.15 / 2);
    float rightLimit = windowWidth - getBounds().width;

    // Wall collision to the left
    if (sprite.getPosition().x < leftLimit)
    {
        sprite.setPosition(leftLimit, sprite.getPosition().y);
    }

    // Wall collision to the right
    else if (sprite.getPosition().x > rightLimit)
    {
        sprite.setPosition(rightLimit, sprite.getPosition().y);
    }
}

bool Player::isDead()
{
    return (getHealth() <= 0);
}