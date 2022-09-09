#include <iostream>
#include <vector>
#include <string>

/************************************************************
                         Class Engine
 ************************************************************/
class Engine {
private:
    int RPM;
    int minRPM;
    int maxRPM;
    std::vector<float> torqueMap;

    float interpolateTorque();

public:
    Engine(const int&, const int&, const int&, std::vector<float>&&);
    Engine(Engine&&);
    Engine(const Engine&) = delete;
    ~Engine();

    float calculateCurrentPower();
    float setRPM();
};

/************************************************************
                        Class Position
 ************************************************************/
class Position {
private:
    float range;

public:
    Position(const float&);
    Position(const Position&);
    ~Position();

    float calculatePosition(const float&, const float) const;
    void setRange(const float&);
};

/************************************************************
                        Class GearBox
 ************************************************************/
class GearBox {
private:
    std::vector<float> ratioMap;
    float inRPM = 0;
    float outRPM = 0;

public:
    GearBox(std::vector<float>&&);
    GearBox(GearBox&&);
    GearBox(const GearBox&) = delete;
    ~GearBox();

    void setInRPM(const float&);
    void setOutRPM(const float&);

    float calculateInRPM(const float&, const float&) const;
    float calculateOutRPM() const;
};

/************************************************************
                        Class TyreSet
 ************************************************************/
class TyreSet {
private:
    float diameter;

public:
    TyreSet(const float&);
    ~TyreSet();
};

/************************************************************
                        Class Atmosphere
 ************************************************************/
class Atmosphere {
private:
    float airDensity;

public:
    Atmosphere(const float&);
    ~Atmosphere();

    float calculateDrag(const float&, const float&) const;
};

/************************************************************
                        Class Car
 ************************************************************/
class Car {
private:
    std::string name;
    int mass;
    float velocity = 0;
    float surfaceArea;

    Position position;
    Engine engine;
    GearBox gearBox;
    TyreSet tyreSet;
    const Atmosphere* atmospherePtr;

public:
    Car(const char*, const int&, const float&, const Position&, Engine&&,
        GearBox&&, TyreSet&&, const Atmosphere* const);
    Car(Car&&);
    Car(const Car&) = delete;
    ~Car();

    float calculateCurrentVelocity(const float&);
    void setVelocity(const float&);
};
