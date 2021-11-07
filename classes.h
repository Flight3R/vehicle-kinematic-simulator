#include <iostream>
#include <vector>
#include <string>


class TestRun {
public:
    float timeDelta = 0.01;

    int test();
};


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
    Car(string, int, float, float, Position*, Engine*, GearBox*, TyreSet*, Atmosphere*);

    float calculateCurrentVelocity(float);
    void setVelocity(float);
};

class Position {
private:
    float range;

public:
    float calculatePosition(float, float);
    void setRange(float);
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
    float airDensity;

public:
    float calculateDrag(float, float);
};
