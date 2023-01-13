#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,800), "yes");
    sf::Texture t;
    t.loadFromFile("assets/back.jpg");
    sf::RectangleShape s(sf::Vector2f(220,360));
    sf::Sprite s2;
    s.setOrigin(220,360);
    s.rotate(90);
    //s.setPosition(0,0);
    s.setTexture(&t);
    s2.setTexture(t);
    //s2.setPosition(50,0);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::White);
        //window.draw(s2);
        window.draw(s);
        window.display();
    }
}