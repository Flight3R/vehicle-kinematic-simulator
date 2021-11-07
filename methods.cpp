#include "classes.h"
using namespace std; 

float Engine::getTorque() {
    int lowPoint = RPM % 100 * 100;
    int highPoint = lowPoint + 100;
    float linearInterpolation = (torqueMap[highPoint] - torqueMap[lowPoint]) /100 * (RPM - lowPoint) + torqueMap[lowPoint];
    return linearInterpolation;
}

void Position::calculatePosition(float speed, float timeDelta=0.01) {
    x = x + speed * timeDelta;
}

void Car::calculateCurrentSpeed() {
    // float enginePower = engine
}