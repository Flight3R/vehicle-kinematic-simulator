#include <iostream>
#include <vector>
#include <string>

/************************************
 *          Class Engine
 ************************************/
class Engine {
private:
    int RPM;
    int minRPM;
    int maxRPM;
    std::vector<float> torqueMap;

    float interpolateTorque();

public:
    Engine(const int&, const int&, const int&, const std::vector<float>&);
    Engine(const Engine&&);
    Engine(const Engine&) = delete;

    float calculateCurrentPower();
    float setRPM();
};

/************************************
 *          Class Position
 ************************************/
class Position {
private:
    float range;

public:
    Position(const float&);

    float calculatePosition(const float&, const float) const;
    void setRange(const float&);
};

/************************************
 *          Class GearBox
 ************************************/
class GearBox {
private:
    std::vector<int> ratioMap;

public:
    GearBox(const std::vector<int>&);
    GearBox(const GearBox&&);
    GearBox(const GearBox&) = delete;

    float calculateRPM(const float&, const float&) const;
};

/************************************
 *          Class TyreSet
 ************************************/
class TyreSet {
private:
    float diameter;

public:
    TyreSet(const float&);
};

/************************************
 *          Class Atmosphere
 ************************************/
class Atmosphere {
private:
    float airDensity;

public:
    Atmosphere(const float&);

    float calculateDrag(const float&, const float&) const;
};

/************************************
 *          Class Car
 ************************************/
class Car {
private:
    std::string name;
    int mass;
    float velocity;
    float surfaceArea;

    Position position;
    Engine engine;
    GearBox gearBox;
    TyreSet tyreSet;
    const Atmosphere* atmospherePtr;

public:
    Car(const char*, const int&, const float&, const float&, const Position&, const Engine&,
        const GearBox&, const TyreSet&, const Atmosphere* const);
    Car(const Car&&);
    Car(const Car&) = delete;

    float calculateCurrentVelocity(const float&);
    void setVelocity(const float&);
};
