#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Fruit.hpp"
#include "Text.hpp"

namespace SnakeGame
{
    class Game
    {
    private:
        const int WindowWidth = 800, WindowHeight = 600;
        const int countFruits = 3;
        bool isRunning = false, isStart = true, isEnd = false;
        int score = 0;
        sf::RenderWindow window;
        SnakeGame::Snake snake;
        std::vector<SnakeGame::Fruit> fruits;
        std::string windowTitle = "Snake Game.";
        SnakeGame::Text StartText, StartSubText, EndText, EndSubText;
        std::string StartTextString = "Snake Game";
        std::string StartSubTextString = "Use arrow keys or WASD to move. Press SPACE to start.";
        std::string EndTextString = "Game Over. Your Score: ";
        std::string EndSubTextString = "Press SPACE to restart. Press ESC to exit.";
        int TextSize = 50;
        int subTextSize = 30;

        int SnakeEatFruit()
        {
            for (int i = 0; i < countFruits; i++)
            {
                if (snake.GetHeadX() == fruits[i].GetX() && snake.GetHeadY() == fruits[i].GetY())
                {
                    return i;
                }
            }
            return -1;
        }

        void Update()
        {
            if (!snake.IsAlive())
            {
                window.setTitle(windowTitle + " Game Over. Score: " + std::to_string(score));
                isRunning = false;
                isEnd = true;
                return;
            }
            if (SnakeEatFruit() >= 0)
            {
                snake.Grow();
                score += 10;
                fruits[SnakeEatFruit()].Create(WindowWidth, WindowHeight);
            }
            snake.Move(WindowWidth, WindowHeight);
            window.setTitle(windowTitle + " Score: " + std::to_string(score));
        };

        void Input()
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::Space:
                        if (!isRunning)
                        {
                            isRunning = true;
                            isStart = false;
                            isEnd = false;
                            StartGame();
                        }
                        break;
                    case sf::Keyboard::A:
                        snake.ChangeDirection(SnakeGame::LEFT);
                        break;
                    case sf::Keyboard::S:
                        snake.ChangeDirection(SnakeGame::DOWN);
                        break;
                    case sf::Keyboard::D:
                        snake.ChangeDirection(SnakeGame::RIGHT);
                        break;
                    case sf::Keyboard::W:
                        snake.ChangeDirection(SnakeGame::UP);
                        break;
                    case sf::Keyboard::Left:
                        snake.ChangeDirection(SnakeGame::LEFT);
                        break;
                    case sf::Keyboard::Right:
                        snake.ChangeDirection(SnakeGame::RIGHT);
                        break;
                    case sf::Keyboard::Up:
                        snake.ChangeDirection(SnakeGame::UP);
                        break;
                    case sf::Keyboard::Down:
                        snake.ChangeDirection(SnakeGame::DOWN);
                        break;
                    default:
                        break;
                    }
                }
            }
        };
        void DrawGame()
        {
            window.clear(sf::Color::Black);
            for (int i = 0; i < countFruits; i++)
            {
                fruits[i].Draw(window);
            }
            snake.Draw(window);
            window.display();
        };

        void DrawStartMenu()
        {
            window.clear(sf::Color::Black);
            StartText.Draw(window);
            StartSubText.Draw(window);
            window.display();
        }

        void DrawEndMenu()
        {
            window.clear(sf::Color::Black);
            EndText.Draw(window);
            EndSubText.Draw(window);
            window.display();
        }

        void StartGame()
        {
            score = 0;
            snake.Init(WindowWidth / 2, WindowHeight / 2);
            fruits.resize(countFruits);
            fruits.clear();
            for (int i = 0; i < countFruits; i++)
            {
                fruits.push_back(SnakeGame::Fruit());
                fruits[i].Create(WindowWidth, WindowHeight);
            }
        }

        void Init()
        {
            srand(time(NULL));
            window.create(sf::VideoMode(WindowWidth, WindowHeight), "Snake Game", sf::Style::Titlebar | sf::Style::Close);
            window.setFramerateLimit(10);
            StartText.Init(StartTextString, TextSize, WindowWidth / 2, WindowHeight / 2);
            StartSubText.Init(StartSubTextString, subTextSize, WindowWidth / 2, WindowHeight / 2 + TextSize * 2);
            EndText.Init(EndTextString + std::to_string(score), TextSize, WindowWidth / 2, WindowHeight / 2);
            EndSubText.Init(EndSubTextString, subTextSize, WindowWidth / 2, WindowHeight / 2 + TextSize * 2);
        };

    public:
        Game()
        {
            Init();
            StartGame();
        };
        ~Game(){

        };

        void Run()
        {
            while (window.isOpen())
            {
                if (isRunning)
                {
                    Input();
                    Update();
                    DrawGame();
                }
                else if (isStart)
                {
                    Input();
                    DrawStartMenu();
                }
                else if (isEnd)
                {
                    Input();
                    DrawEndMenu();
                }
            }
        };
    };
}