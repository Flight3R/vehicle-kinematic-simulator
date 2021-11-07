#include "classes.h"
using namespace std; 

void Position::calculatePosition(float speed, float timeDelta=0.01) {
    x = x + speed * timeDelta;
}

void Atmosphere::calculateDrag(float airDensity, int speed, float surfaceArea) {
    f = (airDensity * speed^3) / 2 * surfaceArea;
}