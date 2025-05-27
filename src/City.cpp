#include "City.hpp"

/*
 City::City()

    :numHumans(100),
    numBuildings(10),
    length(128),
    height(72),
    ValueSwitch(false),
    ValueSwitch2(false),
    seed(0)
    //Intmap(height, std::vector<int>(length, 0))
{ }
*/

City::City()
// Default Values to be used if something goes wrong
    :ValueSwitch(false),
     ValueSwitch2(false), 
     numHumans(100),
     numBuildings(10),
     length(128),
     height(72),
     outputfile(std::string(RESOURCE_DIR) + "/output.csv"),
     seed(321),
     maxIterations(0){

    //inputing data from csv files from an inputted path
    std::string userInput;
    std::string inputfile(std::string(RESOURCE_DIR) + "/config.csv");

<<<<<<< HEAD
    std::cout << "-------Controls-------\n"
        << "escape key - end simulation\n"
        << "+/= -> zoom in\n"
        << "-/_ -> zoom out\n"
        << "arrow keys -> move camera\n"
        << "f -> change speed\n"
        << std::endl;
=======
    //SETTING THE INPUT FILE
//>>>>>>> 464710bb5ff9554c44c1d1aaa14557df16c12e01

    std:: cout << "Input the full path of the config file, leave blank for default (.../resources/config.csv)\n";
    std::getline(std::cin, userInput);
    //TESTING IF IT GENERATES CORRECTLY
    std::ifstream filetest (userInput);
    if (userInput.empty()) {
        std::cout << "Using default path for the input file. \n";
    }
    else if (filetest.is_open()) {
        inputfile = userInput;
    }
    else {
        std::cout << "Failed to create the input file at " << userInput << std::endl << "Reverting to use the default path\n";
    }
    filetest.close();

    //INPUTING THE OUTPUT FILE

    std:: cout << "Input the full path where the output file should be generated, leave blank for default (.../resources/output.csv)\n";
    std::getline(std::cin, userInput);
    //TESTING IF IT IS A PROPER PATH
    std::ofstream filetest2 (userInput);
    if (userInput.empty()) {
        std::cout << "Using default path for output file. \n";
    }
    else if (filetest2.is_open()) {
        outputfile = userInput;
    }
    else {
        std::cout << "Failed to create the output file at " << userInput << std::endl << "Reverting to use the default path\n";
    }
    filetest2.close();

    //READING DATA FROM THE INPUT FILE

    std::ifstream file(inputfile);
    if (file.is_open()) {
        std::string line;


        std::getline(file, line);

        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value;

            std::getline(ss, value, ',');
            seed = std::stoi(value);
            std::getline(ss, value, ',');
            if (std::stoi(value) >= 0) {
                numHumans = std::stoi(value);
            }
            else {
                std::cout << "Incorrect number of humans! \n";
            }
            std::getline(ss, value, ',');
            if (std::stoi(value) >= 0) {
                numBuildings = std::stoi(value);
            }
            else {
                std::cout << "Incorrect number of buildings! \n";
            }
            std::getline(ss, value, ',');
            maxIterations = std::stoi(value);
            std::getline(ss, value, ',');
            if (maxIterations <= 0) {
                std::cout << "Iteration has no limit. Please, press escape to exit simulation \n";
            }
            if (std::stoi(value) > 0) {
                height = std::stoi(value);
            }
            else {
                std::cout << "Incorrect height!\n";
            }
            std::getline(ss, value, ',');
            if (std::stoi(value) > 0) {
                length = std::stoi(value);
            }
            else {
                std::cout << "Incorrect length!\n";
            }
        }

        file.close();
    } else {
        std::cout << "Failed to open file, using default values.\n";
    }

    srand(seed);


}
City::~City() {

}

sf::Texture City::giveTexture(std::string path) {
    return sf::Texture(std::string(RESOURCE_DIR) + "/" + path);;
}


void City::cross(int* level, int width, int length) {

    if (width<=9||length<=9)
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
        for (int i = 0; i < length; ++i) {
            level[i * width + roadColumna] = 2;

            level[i * width + roadColumna + 3] = 2;
        }
        //left to right

        for (int i = 0; i < width; ++i) {
            level[roadColumnb * width + i] = 2;
            level[(roadColumnb + 3) * width + i] = 2;
        }


        if (roadColumnb + 15 < length - 3) {
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
        for (int i = 0; i < length; ++i) {
            level[i * width + roadColumna + 1] = 3;
            level[i * width + roadColumna + 2] = 3;
        }

        //left to right
        for (int i = 0; i < width; ++i) {
            level[(roadColumnb + 1) * width + i] = 3;
            level[(roadColumnb + 2) * width + i] = 3;
        }

        if (roadColumnb + 15 < length - 3) {
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
        std::unique_ptr<Building> building;
        switch (i % 4)
        {
        case 0:
        {
            building = std::make_unique<Shop>();
            break;
        }
        case 1:
        {
            //the fifth building is always a polytechnic, and then every 100th building
            if (i==5||(i!=1&&i%100==1)) {
                building = std::make_unique<Polytechnic>();
            }
            else {
                building = std::make_unique<Hospital>();
            }
            break;
        }
        case 2:
        {
            building = std::make_unique<OfficeBuilding>();
            
            break;
        }
        case 3:
        {
             building = std::make_unique<LiqourShop>();
            
            break;
        }
        
        }
        if (building->Build(Intmap, height, length)) {
            buildings.push_back(std::move(building));
        }

    }
}

void City::createEntities() {

    for (long unsigned int i = 0; i < numHumans; ++i) {
        auto person = std::make_unique<Human>();
        if (rand()%10==0)
        {
            Human* owner = person.get();
            //animal needs raw pointer just like meet
            auto animal = std::make_unique<Dog>(owner);
            entities.push_back(std::move(animal));
        }
        else if (rand()%5==0)
        {
            Human* owner = person.get();
            //animal needs raw pointer just like meet
            auto animal = std::make_unique<Cat>(owner);
            entities.push_back(std::move(animal));
        }
        
        entities.push_back(std::move(person));

        
    }

}

void City::interactionBuilding() {
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
}

void City::interactionHumanBuilding(Entity& entity, Building& building) {
    entity.setTarget(entity.getPosition());
    switch (building.getTile())
    {
    case ShopTile: {
        //ENTITY GETS food
        entity.addHunger(building.getProductValue());
        //ENTITY GETS HAPPINESS
        entity.addHappiness(building.getProductValue()/10);
        //ENTITY PAYS THE PRICE
        entity.addMoney(building.getPrice());
        //BUILDING GETS MONEY
        building.addMoney(-building.getPrice());
        return;
    }
    case HospitalTile: {
        //ENTITY GETS health
        entity.addHealth(building.getProductValue());
        //ENTITY PAYS THE PRICE
        entity.addMoney(building.getPrice());
        //BUILDING GETS MONEY
        building.addMoney(-building.getPrice());
        return;
    }
    case OfficeBuildingTile: {
        //ENTITY GETS money
        entity.addMoney(building.getPrice()*(entity.getSemester() ? entity.getSemester() : 1));
        //BUILDING GETS MONEY
        building.addMoney(building.getPrice());//yeah getPrice is kinda bad but i have no idea how to name it
        return;
    }
    case LiqourShopTile: {
        //ENTITY GETS drunk
        entity.addDrunkness(building.getProductValue());
        //ENTITY GETS HAPPY
        entity.addHappiness(50);
        //ENTITY PAYS THE PRICE
        entity.addMoney(building.getPrice());
        //BUILDING GETS MONEY
        building.addMoney(-building.getPrice());
        return;
    }
        case PolytechnicTile: {
        //ENTITY PAYS FOR DORM
        entity.addMoney(building.getPrice());
        //ENTITY LOSES HAPPINESS
        entity.addHappiness(-(100-building.getProductValue()));
        //ENTITY GETS EDUCATION
        entity.addSemester(1);
        //PWR GETS MONEY
        building.addMoney(-building.getPrice());
        return;
    }
    default:
        return;

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Hyphen) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
        {
            
            view.zoom(1.25f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Equal) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
        {
            
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
        


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
        {
            view = window.getDefaultView();

        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
    {
        sf::sleep(sf::milliseconds(20));
        if (!ValueSwitch)
        {
            ValueSwitch = true;
        }
        else
        {
            ValueSwitch = false;
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
    {
        sf::sleep(sf::milliseconds(20));
        if (!ValueSwitch2)
        {
            ValueSwitch2 = true;
        }
        else
        {
            ValueSwitch2 = false;
        }

    }

}

void City::drawScreen(sf::RenderWindow& window, sf::View& view) {
    //building area
    for (size_t i = 0; i < buildings.size(); i++)
    {
        //draw wants to know your refrence, not your mobile number
        window.draw(*buildings[i]);
    }


    for (size_t i = 0; i < entities.size(); i++)
    {
        
        window.draw(*entities[i]);
        
    }

}


void City::start() {

    int iteration = 0;

    float textX,textY;
    std::string numStr;

    //std::string texturePath = std::string(RESOURCE_DIR) + "/ROLF1.png";
    //pwr logo
    sf::Texture texture = giveTexture("pwr-logo.png");
    sf::Sprite pwr(texture);
    sf::Color currentColor = pwr.getColor();
    pwr.setColor(sf::Color(currentColor.r, currentColor.g, currentColor.b, currentColor.a - 150));
    pwr.setScale(sf::Vector2f(0.25f, 0.25f));



    // size of the window and name
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "City Simulator");
    window.setFramerateLimit(60);

    sf::View view = window.getDefaultView();
    sf::View minimapView = window.getDefaultView();
    





    //maps
    //Do not touch
    std::vector<int> level(height * length);
    std::vector<std::vector<int>> Intmap(height, std::vector<int>(length));

    for (int i = 0; i < height * length; ++i) {
        level[i] = std::rand() % 2;
    }

    cross(level.data(),  length, height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < length; ++x) {
            Intmap[y][x] = level[y * length + x];
        }
    }

    sf::Font font(std::string(RESOURCE_DIR) +"/AGENCYR.TTF");
    sf::Text text(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(5);


    

    createBuildings(Intmap);
    //std::cout << buildings.size();

    //map for entitie, yes i'm lazy but the project does not require ultimate efficiency
    Human mapper ;
    mapper.setMap(Intmap, sf::Vector2i( length, height));
    
    createEntities();

    // create the tilemap from the level definition
    TileMap map;
    if (!map.load(std::string(RESOURCE_DIR) + "/tileset3.png", level.data(), length, height)) {
        std::cout << "Map faild to load";
    }
    
    sf::Vector2 loop{ 0,0 };
    // main loop nothing works without it
    //if the number of iterations is set to 0, the simulation will run forever
    while (window.isOpen() && (maxIterations == 0 || iteration < maxIterations))
    {
        //set a new iteration
        iteration++;
        if (entities.size() > 0)
        {
            entities[0]->setIteration(iteration);
        }
        
  

        camera(window,view);

        //makes program slower
        if (ValueSwitch2)
        {
            sf::sleep(sf::milliseconds(100));
        }
        
        window.setView(view);
        

        
        // drawing shapes
        window.clear();

        window.draw(map);

        
        //window.draw(pwr);

        drawScreen(window, view);


        // debug purposes and it's a lag machine
        if (ValueSwitch)
        {
            for (loop.x = 0; loop.x < height; ++loop.x) {
                for (loop.y = 0; loop.y < length; ++loop.y) {

                    // Draw text
                    numStr = std::to_string(Intmap[loop.x][loop.y]);
                    text.setString(numStr);
                    
                    textX = loop.x * 10 + (10 / 2.0f)-2;
                    textY = loop.y * 10 + (10 / 2.0f)-1; 
                    text.setPosition(sf::Vector2f(textY, textX));
                    window.draw(text);
                }
            }
            loop = { 0,0 };
            
        }
        window.display();
        
        // interact
        if (buildings.size() > 0) {
            interactionBuilding();
        }

        // fight
        if (entities.size() > 1) {
            interactionEntities();
        }

        //walking

        for (int i = 0; i < entities.size(); i++)
        {
            
            entities[i]->walk();

        }
        

    }
    save(Intmap);
}







void City :: save(std::vector<std::vector<int>>& Intmap) {
    //std::cout << "elp1" << std::endl;
    int alive = entities.size() - (entities.size()<= 0 ? 0 : entities[0]->getDeathCount());
    int alivehumans = 0;
    //vector to store all deaths per each iteration
    std::vector<int> deathsPerIteration((entities.size() <= 0 ? 0 : (int)entities[0]->getIteration()) + 1, 0);
    std::vector<int> animalDeathsPerIteration((entities.size() <= 0 ? 0 : (int)entities[0]->getIteration()) + 1, 0);


    std::ofstream file(outputfile);

    //--- Initial Parameters ----
    //std::cout << "elp2" << std::endl;
    file << "Seed,Number of Humans,Number of Buildings,Max Iterations,Map height,Map length\n";
    file << seed << "," << numHumans << "," << numBuildings << ",";
    if (maxIterations == 0) {
        file << "infinity";
    }
    else {
        file << maxIterations;
    }
    file << "," << length << "," << height << "\n";

    // --- Final stats of each building ---
    file << "\nFinal Stats per Building\nID,Name,Price,Product Value,Total Money Earned\n";
    for (long int i = 0; i < buildings.size(); i++) {
        file << buildings[i]->getID() << ","
        << buildings[i]->getName() << ","
        << ((buildings[i]->getPrice()<0)? -buildings[i]->getPrice(): buildings[i]->getPrice() )<< ","
        << buildings[i]->getProductValue() << ","
        << buildings[i]->getMoney() << "\n";
    }
    //std::cout << "elp3" << std::endl;
    // --- Final stats of each human ---
    file << "\nFinal Stats of each Human\nID,Name,Status,Pet ID,Health,Hunger,Happiness,Attack,Defence,Swiftness,Graduated Semesters,Money,Drunkness,Item\n";
    for (long int i = 0; i < entities.size(); i++) {
        if (!entities[i]->getType()) {
            //getting data from toSave method
            file << entities[i]->toSave() << "\n";
            if (!entities[i]->isDead()) {
                alivehumans++;
            }
        }
    }

    // --- Final stats of each animal ---
    file << "\nFinal Stats of each Animal\nID,Type,Owner ID,Status,Health,Hunger,Happiness,Attack,Defence,Swiftness\n";
    for (long int i = 0; i < entities.size(); i++) {
        if (entities[i]->getType()) {
            //getting data from toSave method
            file << entities[i]->toSave() << "\n";
        }
    }
    //std::cout << "elp4" << std::endl;
    // --- Final global stats ---
    file << "\nFinal global stats:\n";
    file << "Total number of entities: " << entities.size() << "\n"
    << "Total number of humans: " << numHumans << "\n"
    << "Total number of animals: " << entities.size() - numHumans << "\n"
    << "Alive entities:" << alive << "\n"
    << "Deaths: " << (entities.size() <= 0 ? 0 : entities[0]->getDeathCount()) << "\n"
    << "Alive humans: " << alivehumans << "\n"
    << "Dead humans: " << numHumans - alivehumans << "\n"
    << "Alive animals: " << alive -  alivehumans << "\n"
    << "Dead animals: " << entities.size() - numHumans - alive + alivehumans << "\n"
    << "Total number of buildings: " << buildings.size() << "\n";

    // --- Stats per each iteration ---
    //std::cout << "elp5" << std::endl;
    for (long int i = 0; i < entities.size(); i++) {
        if (!entities[i]->isDead()) {
            continue;
        }
        deathsPerIteration[entities[i]->getDeathIteration()]++;
        if (entities[i]->getType()) {
            animalDeathsPerIteration[entities[i]->getDeathIteration()]++;
        }
    }

    file << "\nDeaths per Iteration:\nIteration,Total Deaths,Total Remaining Entities,Human Deaths,Remaining Humans,Animal Deaths,Remaining Animals\n";
    alive = entities.size();
    alivehumans = numHumans;
    for (long int i = 0; i < deathsPerIteration.size(); i++) {
        if (deathsPerIteration[i] > 0) {
            alive -= deathsPerIteration[i];
            alivehumans -= (deathsPerIteration[i]-animalDeathsPerIteration[i]);
            file << i << ","
            << deathsPerIteration[i] << ","
            << alive << ","
            << deathsPerIteration[i]-animalDeathsPerIteration[i] << ","
            << alivehumans << ","
            << animalDeathsPerIteration[i] << ","
            << alive - alivehumans << "\n";
        }
    }
    //std::cout << "elp6" << std::endl;
    // --- MAP ---
    file << "\nMap Data:\n";
    for (long  int y = 0; y < height; y++) {
        for (long int x = 0; x < length; x++) {
            file << Intmap[y][x];
            if (x < length - 1) file << ",";
        }
        file << "\n";
    }

    file.close();
    //std::cout << "elp7" << std::endl;
}