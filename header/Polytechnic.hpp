#pragma once
#include "Building.hpp"
//this class inherits basically everything from the building class
//humans can get education here in exchange for money (yes, education is not free, there is no government (yet?))
//pwr also makes humans lose a lot of happiness (realistic), so they often go for a beer afterwards
class Polytechnic : public Building
{
public:
    Polytechnic();
    ~Polytechnic() override = default;


private:

};
