#include "classes.h"
using namespace std; 

void Position::calculatePosition(float speed, float timeDelta=0.01) {
    x = x + speed * timeDelta;
}