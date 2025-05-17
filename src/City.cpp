#include "City.hpp"

City::City()
    :numHumans(100),
    numBuildings(10),
    height(50),
    length(50),
    ValueSwitch(false),
    ValueSwitch2(false)
    //Intmap(length, std::vector<int>(height, 0))
{ }
City::~City() {

}

sf::Texture City::giveTexture(std::string path) {
    return sf::Texture(std::string(RESOURCE_DIR) + "/" + path);;
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


void City::createBuildings(std::vector<std::vector<int>>& Intmap) {
    for (long unsigned int i = 0; i < numBuildings; ++i) {
        switch (i % 4)
        {
        case 0: {
            auto shop = std::make_unique<Shop>();
            if (shop->Build(Intmap, length, height)) {
                buildings.push_back(std::move(shop));
            }
            break;
        }
        case 1: {
            auto hospital = std::make_unique<Hospital>();
            if (hospital->Build(Intmap, length, height)) {
                buildings.push_back(std::move(hospital));
            }
            break;
        }
        case 2: {
            auto Office = std::make_unique<OfficeBuilding>();
            if (Office->Build(Intmap, length, height)) {
                buildings.push_back(std::move(Office));
            }
            break;
        }
        case 3: {
            std::cout << "imnotthere";
            break;
        }
        default: {
            break;
        }
        }

    }
}

void City::createEntities() {

    for (long unsigned int i = 0; i < numHumans; ++i) {
        auto human = std::make_unique<Human>();
        //hmmm I hate this fact 
        //raw pointer is needed
        Human* owner = human.get();
        auto animal = std::make_unique<Animal>(owner);
        //yeah the structer realy matters at least now we know first interaction of animal is always an owner preatty nice
        entities.push_back(std::move(animal));
        entities.push_back(std::move(human));

        
    }

}

void City::interactionEntities() {
    for (size_t i = 0; i < entities.size(); i++)
    {
        //goes throu list faster
        if (entities[i]->isDead())
        {
            continue;
        }
        for (size_t j = i + 1; j < entities.size(); j++) {

            if (entities[j]->isDead())
            {
                continue;
            }
            //real check
            if (entities[i]->getPosition() == entities[j]->getPosition())
            {
                if (rand() % 10 == 0)
                {
                    if (entities[i]->getType()!=human)
                    {
                        entities[i]->fight(entities[j].get());
                    }
                    else
                    {
                        entities[j]->fight(entities[i].get());
                    }
                    //std::cout << "Fight between:" << entities[i]->getID() << " and " << entities[j]->getID() << std::endl;
                    
                }
            }
        }
    }
}

void City::camera(sf::RenderWindow& window, sf::View& view) {
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
        {
            sf::sleep(sf::milliseconds(10));
            view.zoom(1.25f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
        {
            sf::sleep(sf::milliseconds(10));
            view.zoom(0.8f);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {

            view.move(sf::Vector2f(-20, 0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {

            view.move(sf::Vector2f(20, 0));
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            //sf::sleep(sf::milliseconds(100));
            view.move(sf::Vector2f(0, 20));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            //sf::sleep(sf::milliseconds(100));
            view.move(sf::Vector2f(0, -20));
        }

        // shows number tiles
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

        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
        {
            view = window.getDefaultView();

        }

    }
}

void City::start() {

    
    

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

    sf::View view = window.getDefaultView();
    //view.setViewport(sf::FloatRect({ 0.f, 0.f }, { 1.f, 1.f }));
    sf::View minimapView = window.getDefaultView();
    //minimapView.setViewport(sf::FloatRect({ 0.75f, 0.f }, { 0.25f, 0.25f }));

    //human duplication glitch
   
 

    
    
    //maps
    

    //Do not touch
    std::vector<int> level(length * height);
    std::vector<std::vector<int>> Intmap(length, std::vector<int>(height));

    for (int i = 0; i < length * height; ++i) {
        level[i] = std::rand() % 2;
    }

    cross(level.data(),  height, length);

    for (int y = 0; y < length; ++y) {
        for (int x = 0; x < height; ++x) {
            Intmap[y][x] = level[y * height + x];
        }
    }

    sf::Font font(std::string(RESOURCE_DIR) +"/AGENCYR.TTF");
    sf::Text text(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(5);


    

    createBuildings(Intmap);
    std::cout << buildings.size();

    //map for entitie, yes i'm lazy but the project does not require ultimate efficiency
    Human mapper ;
    mapper.setMap(Intmap, sf::Vector2i(length, height));
    
    createEntities();

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(std::string(RESOURCE_DIR) + "/tileset2.png", level.data(), height, length)) {
        std::cout << "Map faild to load";
    }
    
    sf::Vector2 loop{ 0,0 };
    int count=0;
    // main loop nothing works without it
    while (window.isOpen())
    {
        camera(window,view);
       
        
        //interact
        for (size_t i = 0; i < entities.size(); i++)
        {

            if (entities[i]->isDead())
            {
                continue;
            }
            if (entities[i]->getTargetTile() <= 3) 
            {
                continue;
            }
            for (size_t j = 0; j < buildings.size(); j++) {
                switch (entities[i]->getType())
                {
                    case human: 
                    {
                        if (entities[i]->getTargetTile() != buildings[j]->getTile())
                        {

                            continue;
                        }
                        if (!buildings[j]->getGlobalBounds().contains(entities[i]->getPosition())) {
                            continue;
                        }
                        interactionHumanBuilding(*entities[i], *buildings[j]);
                        break;
                    }
                    case animal:
                    {
                        break;
                    }
                    default:
                        break;
                }
                

            }
        }


        //fight
        
        interactionEntities();
    

        //makes program slower
        //sf::sleep(sf::milliseconds(100));
       
        
        
        
        window.setView(view);
        

        
        
        // drawing shapes
        window.clear();

        window.draw(map);

        
        //window.draw(pwr);

        //building area
        for (size_t i = 0; i < buildings.size(); i++)
        {
            //draw wants to know your refrence, not your mobile number
            window.draw(*buildings[i]);
        }
        
        
        for (size_t i = 0; i < entities.size(); i++)
        {
            entities[i]->walk();
            window.draw(*entities[i]);
        }
        
        // debug purposes and it's a lag machine
        if (ValueSwitch)
        {
            for (loop.x = 0; loop.x < length; ++loop.x) {
                for (loop.y = 0; loop.y < height; ++loop.y) {

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





void City::interactionHumanBuilding(Entity& entity, Building& building) {
    entity.setTarget(entity.getPosition());
    switch (building.getTile())
    {
    case ShopTile: {
        //ENTITY GETS food
        entity.setHunger( building.getProductValue());
        //ENTITY PAYS THE PRICE
        entity.setMoney( building.getPrice());
        //BUILDING GETS MONEY
        building.setMoney(-building.getPrice());
        return;
    }
    case HospitalTile: {
        //ENTITY GETS health
        entity.setHealth( building.getProductValue());
        //ENTITY PAYS THE PRICE
        entity.setMoney( building.getPrice());
        //BUILDING GETS MONEY
        building.setMoney( -building.getPrice());
        return;
    }
    case OfficeBuildingTile: {
        //ENTITY GETS Money
        entity.setMoney(building.getProductValue());
        //BUILDING GETS MONEY
        building.setMoney(building.getPrice());//yeah getPrice is kinda bad but i have no idea how to name it
        return;
    }
    case LiqourShopTile:
        return;
    default:
        return;

    }
}

