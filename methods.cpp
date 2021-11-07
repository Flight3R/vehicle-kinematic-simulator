#include "classes.h"
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

void Position::calculatePosition(float speed, float timeDelta=0.01) {
    range = range + speed * timeDelta;
}

void Car::calculateCurrentVelocity() {
    float enginePower = engine->calculateCurrentPower();
    float dragPower = velocity * atmosphere->calculateDrag(velocity, surfaceArea);
}

float Atmosphere::calculateDrag(int velocity, float surfaceArea) {
    f = (airDensity * velocity^3) / 2 * surfaceArea;
}