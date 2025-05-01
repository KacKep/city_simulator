#include <SFML/Graphics.hpp>

int main()
{
    std::string texturePath = std::string(RESOURCE_DIR) + "/ROLF1.png";
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        // Handle loading error
        return -1;
    }
    sf::Sprite sprite(texture);
    
    // size of the window and name
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "City Simulator");
    window.setFramerateLimit(60);

    // shape to draw
    sf::RectangleShape shape(sf::Vector2f(100, 100));
    shape.setFillColor(sf::Color(255,255,255,200));
    

    sf::RectangleShape rect;

    sf::Vector2f rectanglePosition(300,250);

    rect.setPosition(rectanglePosition);
    rect.setSize(sf::Vector2f(100, 100));

    sf::Vector2f behind(50, 50);
    sf::Vector2f behind2(0, 0);

    float xvelocity = 3;
    float yvelocity = 3;

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
        // "physic"

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
        

        // drawing the shape
        window.clear();
        //window.draw(shape);
        window.draw(sprite);
        
        window.draw(rect);
        
        window.display();
        // after effect
        behind2.x = xvelocity * 2;
        behind2.y = yvelocity * 2;
        shape.setPosition(behind = rectanglePosition - behind2);
    }
}


