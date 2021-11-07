#include <iostream>
#include <vector>
#include <string>


class Car {
private:
    string name;
    int mass;
    float speed;

    Position *position;
    Engine *engine;
    GearBox *gearBox;
    TyreSet *tyreSet;
    Atmosphere *atmosphere;
};


class Position {
private:
    float x;
    float y;
};


class Engine {
private:
    vector<int> torqueMap;
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
};
