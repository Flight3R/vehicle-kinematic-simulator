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
    :m_ValueMap(std::move(valueMap))
{
    std::cout << "Create Rotable" << std::endl;
}

Rotable::Rotable(Rotable&& other)
    :m_ValueMap(std::move(other.m_ValueMap))
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
                              m_ValueMap[(inValue + lowPoint) / 10],
                              highPoint,
                              m_ValueMap[(inValue + highPoint) / 10],
                              (float)inValue) * inValue;
}

/************************************************************
                        Methods of Engine
 ************************************************************/
Engine::Engine(const int& RPM, const int& minRPM, const int& maxRPM, std::vector<float>&& torqueMap)
    :Rotable(std::move(torqueMap)), m_RPM(RPM), m_MinRPM(minRPM), m_MaxRPM(maxRPM)
{
    this->m_RPM = RPM >= minRPM ? RPM : minRPM;
    std::cout << "Create Engine" << std::endl;
}

Engine::Engine(Engine&& other)
    :Rotable(std::move(other.m_ValueMap)), m_RPM(other.m_RPM), m_MinRPM(other.m_MinRPM), m_MaxRPM(other.m_MaxRPM)
{
    std::cout << "Create Engine w/m" << std::endl;
}

Engine::~Engine()
{
    std::cout << "Delete Engine" << std::endl;
}

int Engine::getRPM() const
{
    return m_RPM;
}

/************************************************************
                        Methods of Position
 ************************************************************/
Position::Position(const float& range)
    :m_Range(range)
{
    std::cout << "Create Position" << std::endl;
}

Position::Position(const Position& other)
    :m_Range(other.m_Range)
{
    std::cout << "Create Position w/c" << std::endl;
}

Position::~Position()
{
    std::cout << "Delete Position" << std::endl;
}

float Position::calculatePosition(const float& speed, const float timeDelta=0.01) const
{
    return m_Range + speed * timeDelta;
}

void Position::setRange(const float& range)
{
    this->m_Range = range;
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
    :Rotable(std::move(other.m_ValueMap))
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
    : m_Diameter(diameter)
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
    this->m_AirDensity = airDensity;
    std::cout << "Create Atmosphere" << std::endl;
}

Atmosphere::~Atmosphere()
{
    std::cout << "Delete Atmosphere" << std::endl;
}

float Atmosphere::calculateDrag(const float& velocity, const float& surfaceArea) const
{
    return (m_AirDensity * pow(velocity, 3)) / 2 * surfaceArea;
}

/************************************************************
                        Methods of Car
 ************************************************************/
Car::Car(const char* name, const int& mass, const float& surfaceArea, const Position& position,
         Engine&& engine,  GearBox&& gearBox, TyreSet&& tyreSet, const Atmosphere* const atmospherePtr)
    :m_Name(name), m_Mass(mass), m_SurfaceArea(surfaceArea), m_Position(position),
        m_Engine(std::move(engine)), m_GearBox(std::move(gearBox)), m_TyreSet(std::move(tyreSet)),
        m_AtmospherePtr(atmospherePtr)
{
    std::cout << "Create Car" << std::endl;
}

Car::Car(Car&& other)
    :m_Name(std::move(other.m_Name)), m_Mass(other.m_Mass), m_Velocity(other.m_Velocity), m_SurfaceArea(other.m_SurfaceArea), m_Position(std::move(other.m_Position)),
        m_Engine(std::move(other.m_Engine)), m_GearBox(std::move(other.m_GearBox)), m_TyreSet(std::move(other.m_TyreSet)),
        m_AtmospherePtr(other.m_AtmospherePtr)
{
    std::cout << "Create Car w/m" << std::endl;
}

Car::~Car()
{
    std::cout << "Delete Car" << std::endl;
}

float Car::calculateCurrentVelocity(const float& timeDelta)
{
    float enginePower = m_Engine.calculateOutValue(m_Engine.getRPM());
    float dragPower = m_Velocity * m_AtmospherePtr->calculateDrag(m_Velocity, m_SurfaceArea);
    float effectivePower = enginePower - dragPower;
    if (effectivePower < 0) {
        return m_Velocity;
    } else {
        m_Velocity = sqrt(2*effectivePower * timeDelta / m_Mass + pow(m_Velocity, 2));
        return m_Velocity;
    }
}

void Car::setVelocity(const float& velocity)
{
    this->m_Velocity = velocity;
}
