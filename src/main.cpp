#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Draw.hpp"
#include "Human.hpp"
#include "TileMap.hpp"
#include "Building.hpp"
#include "Shop.hpp"



//constexpr int hight = 128;
//constexpr int lenght = 72;

int main()
{
    bool ValueSwitch = false;
    bool keyV;

    //std::string texturePath = std::string(RESOURCE_DIR) + "/ROLF1.png";
    //pwr logo
    sf::Texture texture = giveTexture("pwr-logo.png");
   
    sf::Sprite pwr(texture);
    sf::Color currentColor = pwr.getColor();
    pwr.setColor(sf::Color(currentColor.r, currentColor.g, currentColor.b, currentColor.a-150));
    pwr.setScale(sf::Vector2f(0.25f, 0.25f));

    //seed lol
    srand(time(0)); 
    
    
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
    const int numHumans = 10;

    std::vector<std::shared_ptr<Building>> buildings;
    int buildinfnum = 5;
    //maps
    int hight = 100;
    int lenght = 70;
    //just for sfml
    float hightf = hight;
    float lenghtf = lenght;
    //constexpr int SIZE = hight * lenght;//you can ignore it for teasting for null it gives nothing on map
    
    

    //map generation we need to put it to draw later
     
     
    std::vector<int> level(lenght*hight);
     std::vector<std::vector<int>> Intmap(lenght, std::vector<int>(hight));


    for (int i = 0; i < lenght * hight; ++i) {
        level[i] = std::rand() % 2;  
    }
    
    cross(level.data(), hight, lenght);

    for (int y = 0; y < lenght; ++y) {
        for (int x = 0; x < hight; ++x) {
            Intmap[y][x] = level[y * hight + x];
        }
    }

    sf::Font font("C:\\Windows\\Fonts\\AGENCYR.TTF");
    sf::Text text(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(5);

    
    
    
   
    for (int i = 0; i < 15; ++i) {
        auto shop = std::make_shared<Shop>();
        if (shop->Build(Intmap, lenght, hight)) {
            buildings.push_back(shop);
        }
        
        
    }

    sf::Vector2 a{ lenghtf,hightf };
    for (int i = 0; i < numHumans; ++i) {
        humans.emplace_back(a); 
    }

    
    
    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(std::string(RESOURCE_DIR) + "/tileset2.png", level.data(), hight, lenght))
        return -1;
    sf::Vector2 loop{ 0,0 };
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
            keyV = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V);
            if (keyV)
            {
                if (!ValueSwitch)
                {
                    ValueSwitch = true;
                }
                else
                {
                    ValueSwitch = false;
                }
                keyV = false;
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
        sf::sleep(sf::milliseconds(10));


        // drawing the shape
        window.clear();
       
        window.draw(map);

        //window.draw(shape);
        //window.draw(pwr);
        
        //building area

        for (const auto& building : buildings) {

            window.draw(*building);
        }

        for (auto& human : humans) {
            human.walk(Intmap);
            window.draw(human);
        }

        if (ValueSwitch)
        {
            for (loop.x = 0; loop.x < lenght ; ++loop.x) {
                for (loop.y = 0; loop.y < hight; ++loop.y) {
                
                    // Draw text
                    std::string numStr = std::to_string(Intmap[loop.x][loop.y]);
                    text.setString(numStr);
                    // Center the text in the tile
                    float textX = loop.x * 10 + (10 / 2.0f);
                    float textY= loop.y * 10 + (10 / 2.0f) ; // -5 for visual adjustment
                    text.setPosition(sf::Vector2f(textY, textX));
                    window.draw(text);
                }
            }
            loop = { 0,0 };
        }

        window.draw(rect);

        
        
        
        window.display();

        // after effect
        behind2.x = xvelocity * 2;
        behind2.y = yvelocity * 2;
        shape.setPosition(behind = rectanglePosition - behind2);
    }
    return 0;
}


