#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    const int UP = 0;
    const int DOWN = 1;
    const int LEFT = 2;
    const int RIGHT = 3;

    class Snake
    {
    private:
        float SegmentSize = 20.0f;
        sf::Color SnakeColor = sf::Color::White;
        int SnakeDirection = UP;
        bool isAlive = true;

        std::vector<sf::RectangleShape> SnakeBody;

        sf::RectangleShape CreateSnakeCeil(float X, float Y)
        {
            sf::RectangleShape resultCeil = sf::RectangleShape(sf::Vector2f(SegmentSize, SegmentSize));
            resultCeil.setPosition(X, Y);
            resultCeil.setFillColor(SnakeColor);
            resultCeil.setOutlineColor(sf::Color::Black);
            resultCeil.setOutlineThickness(1.0f);
            resultCeil.setOrigin(SegmentSize / 2, SegmentSize / 2);

            return resultCeil;
        };

        void AddFirstSegment(float X, float Y)
        {
            SnakeBody.emplace(SnakeBody.begin(), CreateSnakeCeil(X, Y));
        }

        void AddLastSegment(float X, float Y)
        {
            SnakeBody.emplace_back(CreateSnakeCeil(X, Y));
        }

        void DeleteLastSegment()
        {
            SnakeBody.pop_back();
        }

        bool CheckCollision(int width, int height)
        {
            if ((SnakeBody[0].getPosition().x <= 0) || (SnakeBody[0].getPosition().x >= width) || (SnakeBody[0].getPosition().y <= 0) || (SnakeBody[0].getPosition().y >= height))
            {
                return true;
            }
            for (int i = 1; i < SnakeBody.size(); i++)
            {
                if (SnakeBody[0].getPosition() == SnakeBody[i].getPosition())
                {
                    return true;
                }
            }
            return false;
        }

    public:
        Snake(){};

        bool IsAlive() { return isAlive; }

        void Grow()
        {
            switch (SnakeDirection)
            {
            case SnakeGame::UP:
                AddLastSegment(SnakeBody[0].getPosition().x, SnakeBody[0].getPosition().y - SegmentSize);
                break;
            case SnakeGame::DOWN:
                AddLastSegment(SnakeBody[0].getPosition().x, SnakeBody[0].getPosition().y + SegmentSize);
                break;
            case SnakeGame::LEFT:
                AddLastSegment(SnakeBody[0].getPosition().x - SegmentSize, SnakeBody[0].getPosition().y);
                break;
            case SnakeGame::RIGHT:
                AddLastSegment(SnakeBody[0].getPosition().x + SegmentSize, SnakeBody[0].getPosition().y);
                break;
            }
        }

        void Init(float start_X, float start_Y)
        {
            isAlive = true;
            SnakeBody.clear();
            ChangeDirection(UP);
            AddFirstSegment(start_X, start_Y);
        };

        void ChangeDirection(int direction)
        {
            SnakeDirection = direction;
        };

        int GetHeadX()
        {
            return SnakeBody[0].getPosition().x;
        };

        int GetHeadY()
        {
            return SnakeBody[0].getPosition().y;
        };

        void Move(float width, float height)
        {
            switch (SnakeDirection)
            {
            case SnakeGame::UP:
                AddFirstSegment(SnakeBody[0].getPosition().x, SnakeBody[0].getPosition().y - SegmentSize);
                DeleteLastSegment();
                break;
            case SnakeGame::DOWN:
                AddFirstSegment(SnakeBody[0].getPosition().x, SnakeBody[0].getPosition().y + SegmentSize);
                DeleteLastSegment();
                break;
            case SnakeGame::LEFT:
                AddFirstSegment(SnakeBody[0].getPosition().x - SegmentSize, SnakeBody[0].getPosition().y);
                DeleteLastSegment();
                break;
            case SnakeGame::RIGHT:
                AddFirstSegment(SnakeBody[0].getPosition().x + SegmentSize, SnakeBody[0].getPosition().y);
                DeleteLastSegment();
                break;
            }

            if (CheckCollision(width, height))
            {
                isAlive = false;
            }
        };
        void Draw(sf::RenderWindow &window)
        {
            for (int i = 0; i < SnakeBody.size(); i++)
            {
                window.draw(SnakeBody[i]);
            }
        };
        ~Snake(){

        };
    };
}
