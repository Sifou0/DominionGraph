#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
// Quand tu hover la carte : monte, decale les autres et scale

std::vector<sf::Texture*> loadTextures(std::vector<std::string> files_names)
{
    std::vector<sf::Texture*> textures;
    for(std::string s : files_names)
    {
        
        sf::Texture* t = new sf::Texture();
        t->loadFromFile("assets/" + s + ".jpg");
        textures.push_back(t);
    }
    
    return textures;
}

std::vector<sf::RectangleShape*> loadCards(std::vector<sf::Texture*> textures)
{
    std::vector<sf::RectangleShape*> cards;
    int i = 0;
    for(std::vector<sf::Texture*>::iterator it = textures.begin() ; it != textures.end() ; ++it)
    {
        sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(220,360)); 
        s->setOrigin(110,180);
        //s->setPosition(sf::Vector2f(150,200));
        s->setTexture(*it);
        s->move(i*100+s->getOrigin().x,s->getOrigin().y);
        i++;
        cards.push_back(s);
    }
    return cards;
}

int main()
{
    std::vector<std::string> files {"background","back","mine"};
    std::vector<sf::Texture*> textures = loadTextures(files);
    std::vector<sf::RectangleShape*> cards = loadCards(textures);
    sf::RenderWindow window(sf::VideoMode(800,800), "yes");
    bool dragged = 0, hover = 0;
    sf::RectangleShape* selectedCard = nullptr;
    float off_x = 0 , off_y = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            
                if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    for(sf::RectangleShape* r : cards)
                    {
                        if(!dragged && r->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                        {
                            dragged = 1;
                            off_x = sf::Mouse::getPosition(window).x - r->getPosition().x;
                            off_y = sf::Mouse::getPosition(window).y - r->getPosition().y;
                            selectedCard = r;
                        }
                    }
                }
                if(event.type == sf::Event::MouseButtonReleased )
                {
                    dragged = 0;
                    //std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
                }
                if(dragged)
                {
                    selectedCard->setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - off_x ,sf::Mouse::getPosition(window).y - off_y)); 
                }
                // if(it->second->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
                // {
                //     it->second->setScale(sf::Vector2f(1.2,1.2));
                //     hover = 1;
                // }
                // if(!it->second->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && hover)
                // {
                //     it->second->setScale(sf::Vector2f(1,1));
                // }
            
            
        }

        window.draw(sf::Sprite(*textures[0]));
        
        for(int i = 1 ; i < cards.size() ; i++)
        {
            window.draw(*cards[i]);
        }
        window.display();
    }
    return 0;
}