//#include <string>
//#include <SFML/Graphics/RenderWindow.hpp>
#include "Draw.hpp"

//easy way to give textures maybe pointless
sf::Texture giveTexture(std::string path) {
    sf::Texture texture;
    if (!texture.loadFromFile(std::string(RESOURCE_DIR) + "/" + path)) {
        // Handle loading error
        return texture;
    }
    return texture;
}

//makes back ground duh
void background(sf::RenderWindow& window, int seed) {
    sf::Texture texture1 = giveTexture("brick1.png");
    sf::Texture texture2 = giveTexture("brick2.png");
    sf::Sprite sprite(texture1);
    sf::Vector2f a = { 0,0 };
    sprite.setPosition(a);
    unsigned int Seed = 10;
    
    //sf::Randomizer::SetSeed(Seed);
    for (; a.x < 1280 ; a.x += 10)
    {
        sprite.setPosition(a);
        for (; a.y < 720; a.y += 10) {
            sprite.setPosition(a);
            if (rand() % 30 == 0) {
                sprite.setTexture(texture2);
                window.draw(sprite);
                sprite.setTexture(texture1);
                continue;
            }
            window.draw(sprite);
        }
        a.y = 0;
    }

}