#include <iostream>
#include <vector>
#include <string>


class Car {
private:
    string name;
    int mass;
    float velocity;
    float surfaceArea;

    Position *position;
    Engine *engine;
    GearBox *gearBox;
    TyreSet *tyreSet;
    Atmosphere *atmosphere;

public:
    void calculateCurrentVelocity();
};


class Position {
private:
    float range;

public:
    void calculatePosition(float, float);
};


class Engine {
private:
    int RPM;
    vector<int> torqueMap;
    float interpolateTorque();

public:    
    float calculateCurrentPower();
};


class GearBox {
private:
    vector<int> ratioMap;
};


class TyreSet {
private:
    float diameter;
};


class Atmosphere {
private:
    int speed;
    float surfaceArea;

public:
    float calculateDrag(int, float);
};
