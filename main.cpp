#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,800), "yes");
    sf::Texture t;
    sf::Texture mine_text;
    t.loadFromFile("assets/background.jpeg");
    mine_text.loadFromFile("assets/mine.jpg");
    sf::RectangleShape rec(sf::Vector2f(220,360));
    bool dragged = 0 , hoover = 0, is_moving = 0;
    int refx = 180, refy = 40;
    rec.setTexture(&mine_text);
    sf::Sprite s(t);
    float off_x = 0 , off_y = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!dragged && rec.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                {
                    dragged = true;
                    off_x = (sf::Mouse::getPosition(window).x - rec.getPosition().x);
                    off_y = (sf::Mouse::getPosition(window).y - rec.getPosition().y);
                }
            }
            if(event.type == sf::Event::MouseButtonReleased )
            {
                dragged = false;
                //std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
            }
            if(dragged)
            {
                std::cout << off_x << " " << off_y<< std::endl;
                rec.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - off_x ,sf::Mouse::getPosition(window).y - off_y));
                
            }
        }
        window.clear(sf::Color::White);
        window.draw(s);
        window.draw(rec);
        window.display();
    }
    return 0;
}