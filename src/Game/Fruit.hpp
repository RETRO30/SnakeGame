#pragma once

#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    class Fruit
    {
    private:
        sf::CircleShape m_circle;
        int fruitSize = 20;

    public:
        Fruit()
        {
            m_circle.setRadius(fruitSize / 2);
            m_circle.setOrigin(fruitSize / 2, fruitSize / 2);
        };

        sf::Color SetRandomColor(sf::Color oldColor)
        {
            sf::Color color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
            while (color == oldColor)
            {
                color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
            }
            return color;
        }

        float GetX() { return m_circle.getPosition().x; };
        float GetY() { return m_circle.getPosition().y; };

        void Draw(sf::RenderWindow &window)
        {
            window.draw(m_circle);
        }

        void Create(int WindowWidth, int WindowHeight)
        {
            m_circle.setFillColor(SetRandomColor(m_circle.getFillColor()));
            m_circle.setPosition((rand() % (WindowWidth / fruitSize - 1) + 1) * fruitSize, (rand() % (WindowHeight / fruitSize - 1) + 1) * fruitSize);
        };

        ~Fruit(){};
    };
};