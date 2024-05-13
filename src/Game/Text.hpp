#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
    class Text
    {
    private:
        sf::Text m_text;
        std::string m_textString;
        sf::Font m_font;
        sf::Color m_color;

    public:
        Text()
        {
            m_textString = "";
            m_color = sf::Color::White;
            if (!m_font.loadFromFile("fonts/font.ttf"))
            {
                exit(-1);
            }
            m_text.setFont(m_font);
            m_text.setFillColor(m_color);
        }

        void Init(std::string text, int size, float x, float y)
        {
            SetText(text);
            SetSize(size);
            SetPosition(x, y);
        }

        void Draw(sf::RenderWindow &window)
        {
            m_text.setString(m_textString);
            m_text.setFont(m_font);
            m_text.setFillColor(m_color);
            window.draw(m_text);
        }

        void SetPosition(float x, float y)
        {
            m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
            m_text.setPosition(x, y);
        }

        void SetSize(int size) { m_text.setCharacterSize(size); }

        void SetText(std::string text) { m_textString = text; }
    };
};
