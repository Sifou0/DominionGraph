#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
// Quand tu hover la carte : monte, decale les autres et scale

std::map<std::string,sf::Texture> loadTextures(std::vector<std::string> files_names)
{
    std::map<std::string,sf::Texture> textures;
    for(std::string s : files_names)
    {
        sf::Texture t;
        t.loadFromFile("assets/" + s + ".jpg");
        textures.insert(std::pair<std::string,sf::Texture>(s,t));
    }
    return textures;
}

std::map<std::string,sf::RectangleShape> loadCards(std::map<std::string,sf::Texture> textures)
{
    std::map<std::string,sf::RectangleShape> cards;
    for(std::map<std::string,sf::Texture>::iterator it = textures.begin() ; it != textures.end() ; ++it)
    {
        sf::RectangleShape r;
        r.setTexture(&it->second);
        cards.insert(std::pair<std::string,sf::RectangleShape>(it->first,r));
    }
    return cards;
}

int main()
{
    std::vector<std::string> files {"background","mine","back"};
    std::map<std::string,sf::Texture> textures = loadTextures(files);
    sf::RenderWindow window(sf::VideoMode(800,800), "yes");
    sf::RectangleShape rec(sf::Vector2f(220,360));
    sf::RectangleShape pioche(sf::Vector2f(220,360));
    bool dragged = 0, hover = 0;
    rec.setTexture(&textures.at("mine"));
    float off_x = 0 , off_y = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // if(!dragged && rec.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                // {
                //     dragged = true;
                //     off_x = sf::Mouse::getPosition(window).x - rec.getPosition().x;
                //     off_y = sf::Mouse::getPosition(window).y - rec.getPosition().y;
                // }

            }
            if(event.type == sf::Event::MouseButtonReleased )
            {
                dragged = false;
                //std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
            }
            if(dragged)
            {
                //std::cout << off_x << " " << off_y<< std::endl;
                rec.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - off_x ,sf::Mouse::getPosition(window).y - off_y));
                
            }
            if(rec.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
            {
                rec.setScale(sf::Vector2f(1.2,1.2));
                hover = 1;
            }
            if(!rec.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && hover)
            {
                rec.setScale(sf::Vector2f(1,1));
            }
        }
        window.clear(sf::Color::White);
        window.draw(sf::Sprite(textures.at("background")));
        window.draw(rec);
        window.display();
    }
    return 0;
}