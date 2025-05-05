#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Draw.hpp"
#include "Human.hpp"
#include "TileMap.hpp"


int main()
{
    //std::string texturePath = std::string(RESOURCE_DIR) + "/ROLF1.png";
    //pwr logo
    sf::Texture texture = giveTexture("pwr-logo.png");
   
    sf::Sprite sprite(texture);
    sf::Color currentColor = sprite.getColor();
    sprite.setColor(sf::Color(currentColor.r, currentColor.g, currentColor.b, currentColor.a-150));
    sprite.setScale(sf::Vector2f(0.25f, 0.25f));

    //seed lol
    srand(120); 
    
    
    // size of the window and name
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "City Simulator");
    window.setFramerateLimit(60);

    // shape to draw
    sf::RectangleShape shape(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color(255,255,255,200));
    
    //bouncy square for the lols
    sf::RectangleShape rect;

    sf::Vector2f rectanglePosition(300,250);

    rect.setPosition(rectanglePosition);
    rect.setSize(sf::Vector2f(100, 100));

    sf::Vector2f behind(50, 50);
    sf::Vector2f behind2(0, 0);

    float xvelocity = 3;
    float yvelocity = 3;


    //human duplication glitch
    std::vector<Human> humans;
    const int numHumans = 20;

    for (int i = 0; i < numHumans; ++i) {
        humans.emplace_back(i); // assuming Human(int seed) constructor // it's useless with the seed it does nothing rn
    }

    //map generation we need to put it to draw later 
    constexpr int size = 128 * 72;
    std::array<int, size> level;

    

    for (int i = 0; i < size; ++i) {
        level[i] = std::rand() % 4;  
    }
    
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(std::string(RESOURCE_DIR) + "/tileset.png", {10, 10}, level.data(), 128, 72))
        return -1;

    // main loop nothing works without it
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // closing window with the "X" button top right corner
            if (event->is<sf::Event::Closed>())
                window.close();

            // closing window with escape key
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();
            }
        }
        // "physic" of the bouncy square

        rectanglePosition.x += xvelocity;
        rectanglePosition.y += yvelocity;
        if (rectanglePosition.x<0 || rectanglePosition.x>1280-100)
        {
            xvelocity *= -1;
        }
        if (rectanglePosition.y<0 || rectanglePosition.y>720-100)
        {
            yvelocity *= -1;
        }
        rect.setPosition(rectanglePosition);


        //shape.setPosition(rect.getPosition() - behind);
        
        //makes program slower
        //sf::sleep(sf::milliseconds(100));


        // drawing the shape
        window.clear();
       
        window.draw(map);

        window.draw(shape);
        window.draw(sprite);

        

        window.draw(rect);
        for (auto& human : humans) {
            human.walk();        
            window.draw(human);  
        }
        
        
        window.display();

        // after effect
        behind2.x = xvelocity * 2;
        behind2.y = yvelocity * 2;
        shape.setPosition(behind = rectanglePosition - behind2);
    }
}


