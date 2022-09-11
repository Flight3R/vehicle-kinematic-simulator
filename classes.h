#include <iostream>
#include <vector>
#include <string>

/************************************************************
                         Class Rotable
 ************************************************************/
class Rotable
{
protected:
    std::vector<float> valueMap;
public:
    Rotable(std::vector<float>&&);
    Rotable(Rotable&&);
    Rotable(const Rotable&) = delete;
    ~Rotable();

    virtual float calculateOutValue(const float&) const;
};

/************************************************************
                         Class Engine
 ************************************************************/
class Engine : public Rotable
{
private:
    int minRPM;
    int maxRPM;
    int RPM;

public:
    Engine(const int&, const int&, const int&, std::vector<float>&&);
    Engine(Engine&&);
    Engine(const Engine&) = delete;
    ~Engine();

    float setRPM();
    int getRPM() const;
};

/************************************************************
                        Class Position
 ************************************************************/
class Position
{
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
class GearBox : public Rotable
{
public:
    GearBox(std::vector<float>&&);
    GearBox(GearBox&&);
    GearBox(const GearBox&) = delete;
    ~GearBox();
};

/************************************************************
                        Class TyreSet
 ************************************************************/
class TyreSet
{
private:
    float diameter;

public:
    TyreSet(const float&);
    ~TyreSet();
};

/************************************************************
                        Class Atmosphere
 ************************************************************/
class Atmosphere
{
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
class Car
{
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
