#include "City.hpp"

City::City() {

}
City::~City() {

}

sf::Texture City::giveTexture(std::string path) {
    return sf::Texture(std::string(RESOURCE_DIR) + "/" + path);;
}

//makes back ground duh
void City::background(sf::RenderWindow& window, int seed) {
    sf::Texture texture1 = giveTexture("brick1.png");
    sf::Texture texture2 = giveTexture("brick2.png");
    sf::Sprite sprite(texture1);
    sf::Vector2f a = { 0,0 };
    sprite.setPosition(a);
    unsigned int Seed = 10;

    //sf::Randomizer::SetSeed(Seed);
    for (; a.x < 1280; a.x += 10)
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

void City::cross(int* level, int width, int height) {

    if (width<=9||height<=9)
    {
        std::cout << "no road today";
        return;
    }
    int roadColumnb = std::rand() % 5;
    int roadColumna = std::rand() % 5;
    int rb = roadColumnb;
    int ra = roadColumna;
    bool h = false;
    bool l = false;
    for (; ; )
    {

        //walk of 2
        for (int i = 0; i < height; ++i) {
            level[i * width + roadColumna] = 2;

            level[i * width + roadColumna + 3] = 2;
        }
        //left to right

        for (int i = 0; i < width; ++i) {
            level[roadColumnb * width + i] = 2;
            level[(roadColumnb + 3) * width + i] = 2;
        }


        if (roadColumnb + 15 < height - 3) {
            roadColumnb += 15;
        }
        else
        {
            h = true;
        }
        if (roadColumna + 15 < width - 3) {
            roadColumna += 15;
        }
        else
        {
            l = true;
        }
        if (l && h) {
            break;
        }
    }

    roadColumnb = rb;
    roadColumna = ra;
    h = l = false;

    for (; ; )
    {

        //road of 3
        for (int i = 0; i < height; ++i) {
            level[i * width + roadColumna + 1] = 3;
            level[i * width + roadColumna + 2] = 3;
        }

        //left to right
        for (int i = 0; i < width; ++i) {
            level[(roadColumnb + 1) * width + i] = 3;
            level[(roadColumnb + 2) * width + i] = 3;
        }

        if (roadColumnb + 15 < height - 3) {
            roadColumnb += 15;
        }
        else
        {
            h = true;
        }
        if (roadColumna + 15 < width - 3) {
            roadColumna += 15;
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


void City::start() {


    bool ValueSwitch = false;
    bool keyV;

    //std::string texturePath = std::string(RESOURCE_DIR) + "/ROLF1.png";
    //pwr logo
    sf::Texture texture = giveTexture("pwr-logo.png");

    sf::Sprite pwr(texture);
    sf::Color currentColor = pwr.getColor();
    pwr.setColor(sf::Color(currentColor.r, currentColor.g, currentColor.b, currentColor.a - 150));
    pwr.setScale(sf::Vector2f(0.25f, 0.25f));

    //seed lol
    srand(time(0));


    // size of the window and name
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "City Simulator");
    window.setFramerateLimit(60);





    //human duplication glitch
    std::vector<std::unique_ptr<Entity>> entities;
    const int numHumans = 1;

    std::vector<std::unique_ptr<Building>> buildings;
    int numbuildin = 10;
    //maps
    int hight =50;
    int lenght = 72;
    //just for sfml
    float hightf = hight;
    float lenghtf = lenght;
    //constexpr int SIZE = hight * lenght;//you can ignore it for teasting for null it gives nothing on map



    //map generation we need to put it to draw later


    std::vector<int> level(lenght * hight);
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

    sf::Font font(std::string(RESOURCE_DIR) +"/AGENCYR.TTF");
    sf::Text text(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(5);


    
    buildings.push_back(std::make_unique<Building>());

    for (int i = 0; i < numbuildin; ++i) {
        switch (i%4)
        {
        case 0: {
            auto shop = std::make_unique<Shop>();
            if (shop->Build(Intmap, lenght, hight)) {
                buildings.push_back(std::move(shop));
            }
            break;
        }
        case 1: {
            auto hospital = std::make_unique<Hospital>();
            if (hospital->Build(Intmap, lenght, hight)) {
                buildings.push_back(std::move(hospital));
            }
            break;
        }
        case 2: {
            auto Office = std::make_unique<OfficeBuilding>();
            if (Office->Build(Intmap, lenght, hight)) {
                buildings.push_back(std::move(Office));
            }
        }
        default:
            break;
        }
        auto shop = std::make_unique<Shop>();
        if (shop->Build(Intmap, lenght, hight)) {
            buildings.push_back(std::move(shop));
        }
    }
    std::cout << buildings.size();

    //map fo entitie yes i'm lazy but the project does not require ultimate efficiency
    Human2 *mapper = new Human2();
    mapper->setMap(Intmap, sf::Vector2i(lenght, hight));
    delete mapper;
    
    

    sf::Vector2 a{ lenghtf,hightf };//rn fir human the original

    for (int i = 0; i < numHumans; ++i) {
        auto human = std::make_unique<Human2>();
        entities.push_back(std::move(human));
    }



    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(std::string(RESOURCE_DIR) + "/tileset2.png", level.data(), hight, lenght)) {
        std::cout << "Map faild to load";
    }

    sf::Vector2 loop{ 0,0 };
    int count=0;
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
            {
                sf::sleep(sf::milliseconds(100));
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
        
        for (size_t i = 0; i < entities.size(); i++)
        {
            if (entities[i]->getDead())
            {
                continue;
            }
            for (size_t j = 0; j < buildings.size(); j++) {
                if (*entities[i] == *buildings[j])
                {
                    std::cout << "\ni'm a building don't be a racist"<< count++;
                }
            }
        }



        //shape.setPosition(rect.getPosition() - behind);

        //makes program slower
        sf::sleep(sf::milliseconds(10));


        // drawing the shape
        window.clear();

        window.draw(map);

        //window.draw(shape);
        //window.draw(pwr);

        //building area
        for (size_t i = 0; i < buildings.size(); i++)
        {
            window.draw(*buildings[i]);
        }
         /*for (const auto& building : buildings) {

                window.draw(*building);
            }*/
        
        
        

        for (size_t i = 0; i < entities.size(); i++)
        {
            entities[i]->walk();
            window.draw(*entities[i]);
        }
        /*for (auto& human : humans) {
            human.walk(Intmap);
            window.draw(human);
        }*/

        if (ValueSwitch)
        {
            for (loop.x = 0; loop.x < lenght; ++loop.x) {
                for (loop.y = 0; loop.y < hight; ++loop.y) {

                    // Draw text
                    std::string numStr = std::to_string(Intmap[loop.x][loop.y]);
                    text.setString(numStr);
                    
                    float textX = loop.x * 10 + (10 / 2.0f)-2;
                    float textY = loop.y * 10 + (10 / 2.0f)-1; 
                    text.setPosition(sf::Vector2f(textY, textX));
                    window.draw(text);
                }
            }
            loop = { 0,0 };
        }

        window.display();
    }
}

// it's for the funny // I see people hating me for this
bool operator==(Entity& entity, Building& building) {
    if (!building.getGlobalBounds().contains(entity.getPosition())){
        return false;
    }
    
    std::cout << entity.getTargetTile() << std::endl;
    if (entity.getTargetTile()!=building.getTile())
    {

        return false;
    }
    switch (entity.getType())
    {
    case human:
        switch (building.getTile())
        {
        case ShopTile: {
            //ENTITY GETS food
            entity.setHunger(entity.getHunger() + building.getProductValue());
            //ENTITY PAYS THE PRICE
            entity.setMoney(entity.getMoney() + building.getPrice());
            //BUILDING GETS MONEY
            building.setMoney(building.getMoney() - building.getMoney());
            break;
        }
        case HospitalTile: {
            //ENTITY GETS health
            entity.setHealth(entity.getHealth() + building.getProductValue());
            //ENTITY PAYS THE PRICE
            entity.setMoney(entity.getMoney() + building.getPrice());
            //BUILDING GETS MONEY
            building.setMoney(building.getMoney() - building.getMoney());
            break;
        }
        case OfficeBuildingTile: {
            //ENTITY GETS Money
            entity.setMoney(entity.getMoney() + building.getProductValue());
            //BUILDING GETS MONEY
            building.setMoney(building.getMoney() + building.getPrice());//yeah getPrice is kinda bad but i have no idea how to name it
            break;
        }
        case LiqourShopTile:
            return true;
        default:
            return true;
            
        }
        break;
    case animal:
    default:
        break;
    }

    return true;
}