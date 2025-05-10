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

void road(int* level, int width, int height) {
    int roadColb = std::rand() % 5;
    int roadCol = std::rand() % 5;
    int rb = roadColb;
    int ra = roadCol;
    bool h = false;
    bool l = false;
    for (; ; )
    {

        //walk of 2
        for (int i = 0; i < height; ++i) {
            level[i * width + roadCol] = 2;

            level[i * width + roadCol + 3] = 2;
        }
        //left to right

        for (int i = 0; i < width; ++i) {
            level[roadColb * width + i] = 2;
            level[(roadColb + 3) * width + i] = 2;
        }


        if (roadColb + 15 < height - 3) {
            roadColb += 15;
        }
        else
        {
            h = true;
        }
        if (roadCol + 15 < width - 3) {
            roadCol += 15;
        }
        else
        {
            l = true;
        }
        if (l && h) {
            break;
        }
    }

    roadColb = rb;
    roadCol = ra;
    h = l = false;

    for (; ; )
    {

        //road of 4
        for (int i = 0; i < height; ++i) {
            level[i * width + roadCol + 1] = 3;
            level[i * width + roadCol + 2] = 3;
        }

        //left to right
        for (int i = 0; i < width; ++i) {
            level[(roadColb + 1) * width + i] = 3;
            level[(roadColb + 2) * width + i] = 3;
        }

        if (roadColb + 15 < height - 3) {
            roadColb += 15;
        }
        else
        {
            h = true;
        }
        if (roadCol + 15 < width - 3) {
            roadCol += 15;
        }
        else
        {
            l = true;
        }
        if (l && h) {
            break;
        }
    }
}