#include "classes.h"
#include <cmath>

template <typename T>
T interpolate(T x0, T y0, T x1, T y1, T x)
{
    T linearInterpolation = (y1 - y0) / (x1 - x0) * (x - x0) + y0;
    return linearInterpolation;
}

/************************************
 *          Class Engine
 ************************************/
Engine::Engine(const int& RPM, const int& minRPM, const int& maxRPM, const std::vector<float>& torqueMap)
    :RPM(RPM), minRPM(minRPM), maxRPM(maxRPM), torqueMap(std::move(torqueMap))
{
}

Engine::Engine(const Engine&& other)
    :RPM(other.RPM), minRPM(other.minRPM), maxRPM(other.maxRPM), torqueMap(std::move(other.torqueMap))
{
}

float Engine::interpolateTorque()
{
    float lowPoint = RPM % 100 * 100;
    float highPoint = lowPoint + 100;
    return interpolate<float>(lowPoint,
                              torqueMap[(RPM + lowPoint) / 10],
                              highPoint,
                              torqueMap[(RPM + highPoint) / 10],
                              (float)RPM);
}

float Engine::calculateCurrentPower()
{
    return interpolateTorque() * RPM;
}

/************************************
 *          Class Position
 ************************************/
Position::Position(const float& range)
    :range(range)
{
}

float Position::calculatePosition(const float& speed, const float timeDelta=0.01) const
{
    return range + speed * timeDelta;
}

void Position::setRange(const float& range)
{
    this->range = range;
}

/************************************
 *          Class GearBox
 ************************************/
GearBox::GearBox(const std::vector<int>& ratioMap)
    :ratioMap(std::move(ratioMap))
{
}

GearBox::GearBox(const GearBox&& other)
    :ratioMap(std::move(other.ratioMap))
{
}

float GearBox::calculateRPM(const float& velocity, const float& diameter) const
{
    return velocity / diameter / M_PI;
}

/************************************
 *          Class TyreSet
 ************************************/
TyreSet::TyreSet(const float& diameter)
    : diameter(diameter)
{
}

/************************************
 *          Class Atmosphere
 ************************************/
Atmosphere::Atmosphere(const float& airDensity)
{
    this->airDensity = airDensity;
}

float Atmosphere::calculateDrag(const float& velocity, const float& surfaceArea) const
{
    return (airDensity * pow(velocity, 3)) / 2 * surfaceArea;
}

/************************************
 *          Class Car
 ************************************/
Car::Car(const char* name, const int& mass, const float& velocity, const float& surfaceArea, const Position& position,
         const Engine& engine, const GearBox& gearBox, const TyreSet& tyreSet, const Atmosphere* const atmospherePtr)
    :name(name), mass(mass), velocity(velocity), surfaceArea(surfaceArea), position(std::move(position)),
        engine(std::move(engine)), gearBox(std::move(gearBox)), tyreSet(std::move(tyreSet)),
        atmospherePtr(atmospherePtr)
{
}

Car::Car(const Car&& other)
    :name(std::move(other.name)), mass(other.mass), velocity(other.velocity), surfaceArea(other.surfaceArea), position(std::move(other.position)),
        engine(std::move(other.engine)), gearBox(std::move(other.gearBox)), tyreSet(std::move(other.tyreSet)),
        atmospherePtr(other.atmospherePtr)
{
}

float Car::calculateCurrentVelocity(const float& timeDelta)
{
    float enginePower = engine.calculateCurrentPower();
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
