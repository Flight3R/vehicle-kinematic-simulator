#include "classes.h"
#include <cmath>

template <typename T>
T interpolate(T x0, T y0, T x1, T y1, T x)
{
    T linearInterpolation = (y1 - y0) / (x1 - x0) * (x - x0) + y0;
    return linearInterpolation;
}

/************************************************************
                        Methods of Rotable
 ************************************************************/
Rotable::Rotable(std::vector<float>&& valueMap)
    :valueMap(std::move(valueMap))
{
    std::cout << "Create Rotable" << std::endl;
}

Rotable::Rotable(Rotable&& other)
    :valueMap(std::move(other.valueMap))
{
    std::cout << "Create Rotable w/m" << std::endl;
}

Rotable::~Rotable()
{
    std::cout << "Delete Rotable" << std::endl;
}

float Rotable::calculateOutValue(const float& inValue) const
{
    int lowPoint = (int)inValue % 100 * 100;
    int highPoint = lowPoint + 100;
    return interpolate<float>(lowPoint,
                              valueMap[(inValue + lowPoint) / 10],
                              highPoint,
                              valueMap[(inValue + highPoint) / 10],
                              (float)inValue) * inValue;
}

/************************************************************
                        Methods of Engine
 ************************************************************/
Engine::Engine(const int& RPM, const int& minRPM, const int& maxRPM, std::vector<float>&& torqueMap)
    :Rotable(std::move(torqueMap)), RPM(RPM), minRPM(minRPM), maxRPM(maxRPM)
{
    this->RPM = RPM >= minRPM ? RPM : minRPM;
    std::cout << "Create Engine" << std::endl;
}

Engine::Engine(Engine&& other)
    :Rotable(std::move(other.valueMap)), RPM(other.RPM), minRPM(other.minRPM), maxRPM(other.maxRPM)
{
    std::cout << "Create Engine w/m" << std::endl;
}

Engine::~Engine()
{
    std::cout << "Delete Engine" << std::endl;
}

int Engine::getRPM() const
{
    return RPM;
}

/************************************************************
                        Methods of Position
 ************************************************************/
Position::Position(const float& range)
    :range(range)
{
    std::cout << "Create Position" << std::endl;
}

Position::Position(const Position& other)
    :range(other.range)
{
    std::cout << "Create Position w/c" << std::endl;
}

Position::~Position()
{
    std::cout << "Delete Position" << std::endl;
}

float Position::calculatePosition(const float& speed, const float timeDelta=0.01) const
{
    return range + speed * timeDelta;
}

void Position::setRange(const float& range)
{
    this->range = range;
}

/************************************************************
                        Methods of GearBox
 ************************************************************/
GearBox::GearBox(std::vector<float>&& ratioMap)
    :Rotable(std::move(ratioMap))
{
    std::cout << "Create GearBox" << std::endl;
}

GearBox::GearBox(GearBox&& other)
    :Rotable(std::move(other.valueMap))
{
    std::cout << "Create GearBox w/m" << std::endl;
}

GearBox::~GearBox()
{
    std::cout << "Delete GearBox" << std::endl;
}

/************************************************************
                        Methods of TyreSet
 ************************************************************/
TyreSet::TyreSet(const float& diameter)
    : diameter(diameter)
{
    std::cout << "Create TyreSet" << std::endl;
}

TyreSet::~TyreSet()
{
    std::cout << "Delete TyreSet" << std::endl;
}

/************************************************************
                    Methods of Atmosphere
 ************************************************************/
Atmosphere::Atmosphere(const float& airDensity)
{
    this->airDensity = airDensity;
    std::cout << "Create Atmosphere" << std::endl;
}

Atmosphere::~Atmosphere()
{
    std::cout << "Delete Atmosphere" << std::endl;
}

float Atmosphere::calculateDrag(const float& velocity, const float& surfaceArea) const
{
    return (airDensity * pow(velocity, 3)) / 2 * surfaceArea;
}

/************************************************************
                        Methods of Car
 ************************************************************/
Car::Car(const char* name, const int& mass, const float& surfaceArea, const Position& position,
         Engine&& engine,  GearBox&& gearBox, TyreSet&& tyreSet, const Atmosphere* const atmospherePtr)
    :name(name), mass(mass), surfaceArea(surfaceArea), position(position),
        engine(std::move(engine)), gearBox(std::move(gearBox)), tyreSet(std::move(tyreSet)),
        atmospherePtr(atmospherePtr)
{
    std::cout << "Create Car" << std::endl;
}

Car::Car(Car&& other)
    :name(std::move(other.name)), mass(other.mass), velocity(other.velocity), surfaceArea(other.surfaceArea), position(std::move(other.position)),
        engine(std::move(other.engine)), gearBox(std::move(other.gearBox)), tyreSet(std::move(other.tyreSet)),
        atmospherePtr(other.atmospherePtr)
{
    std::cout << "Create Car w/m" << std::endl;
}

Car::~Car()
{
    std::cout << "Delete Car" << std::endl;
}

float Car::calculateCurrentVelocity(const float& timeDelta)
{
    float enginePower = engine.calculateOutValue(engine.getRPM());
    float dragPower = velocity * atmospherePtr->calculateDrag(velocity, surfaceArea);
    float effectivePower = enginePower - dragPower;
    if (effectivePower < 0) {
        return velocity;
    } else {
        velocity = sqrt(2*effectivePower * timeDelta / mass + pow(velocity, 2));
        return velocity;
    }
}

void Car::setVelocity(const float& velocity)
{
    this->velocity = velocity;
}
