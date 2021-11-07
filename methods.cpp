#include "classes.h"
#include <cmath>
using namespace std; 

float Engine::interpolateTorque() {
    int lowPoint = RPM % 100 * 100;
    int highPoint = lowPoint + 100;
    float linearInterpolation = (torqueMap[highPoint] - torqueMap[lowPoint]) /100 * (RPM - lowPoint) + torqueMap[lowPoint];
    return linearInterpolation;
}

float Engine::calculateCurrentPower() {
    return interpolateTorque() * RPM;
}

float Position::calculatePosition(float speed, float timeDelta=0.01) {
    return range + speed * timeDelta;
}

void Position::setRange(float range) {
    this->range = range;
}

float Car::calculateCurrentVelocity(float timeDelta) {
    float enginePower = engine->calculateCurrentPower();
    float dragPower = velocity * atmosphere->calculateDrag(velocity, surfaceArea);
    float effectivePower = enginePower - dragPower;
    if (effectivePower < 0) {
        return velocity;
    } else {
        velocity = sqrt(2*effectivePower * timeDelta / mass + pow(velocity, 2));
        return velocity;
    }
}

void Car::setVelocity(float velocity) {
    this->velocity = velocity;
}

float Atmosphere::calculateDrag(float velocity, float surfaceArea) {
    return (airDensity * pow(velocity, 3)) / 2 * surfaceArea;
}

int TestRun::test() {
    return 0;
}

Car::Car(string name, int mass, float velocity, float surfaceArea, Position *position, Engine *engine, GearBox *gearBox, TyreSet *tyreSet, Atmosphere *atmosphere) {
    this->name = name;
}