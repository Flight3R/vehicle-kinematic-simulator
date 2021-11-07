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
    Car(string, int, float, float, Position*, Engine*, GearBox*, TyreSet*, Atmosphere*);

    float calculateCurrentVelocity(float);
    void setVelocity(float);
};

class Position {
private:
    float range;

public:
    Position(float);

    float calculatePosition(float, float);
    void setRange(float);
};

class Engine {
private:
    int RPM;
    int minRPM;
    int maxRPM;
    vector<int> torqueMap;

    float interpolateTorque();

public:    
    Engine(int, int, int, vector<int>);

    float calculateCurrentPower();
    float setRPM();
};

class GearBox {
private:
    vector<int> ratioMap;

public:
    GearBox(vector<int>);

    float calculateRPM(float, float);
};

class TyreSet {
private:
    float diameter;

public:
    TyreSet(float);
};

class Atmosphere {
private:
    float airDensity;

public:
    Atmosphere(float);

    float calculateDrag(float, float);
};
