#include <iostream>
#include <vector>
#include <string>

/*******************************************************************************
 * Class Rotable
 ******************************************************************************/
class Rotable
{
protected:
    std::vector<float> m_ValueMap;
public:
    Rotable(std::vector<float>&&);
    Rotable(Rotable&&);
    Rotable(const Rotable&) = delete;
    virtual ~Rotable() = 0;

    virtual float calculateOutValue(const float&) const;
};

/*******************************************************************************
 * Class Engine
 ******************************************************************************/
class Engine : public Rotable
{
private:
    int m_MinRPM;
    int m_MaxRPM;
    int m_RPM;

public:
    Engine(const int&, const int&, const int&, std::vector<float>&&);
    Engine(Engine&&);
    Engine(const Engine&) = delete;
    ~Engine();

    float setRPM();
    int getRPM() const;
};

/*******************************************************************************
 * Class Position
 ******************************************************************************/
class Position
{
private:
    float m_Range;

public:
    Position(const float&);
    Position(const Position&);
    ~Position();

    float calculatePosition(const float&, const float) const;
    void setRange(const float&);
};

/*******************************************************************************
 * Class GearBox
 ******************************************************************************/
class GearBox : public Rotable
{
public:
    GearBox(std::vector<float>&&);
    GearBox(GearBox&&);
    GearBox(const GearBox&) = delete;
    ~GearBox();
};

/*******************************************************************************
 * Class TyreSet
 ******************************************************************************/
class TyreSet
{
private:
    float m_Diameter;

public:
    TyreSet(const float&);
    ~TyreSet();
};

/*******************************************************************************
 * Class Atmosphere
 ******************************************************************************/
class Atmosphere
{
private:
    float m_AirDensity;

public:
    Atmosphere(const float&);
    ~Atmosphere();

    float calculateDrag(const float&, const float&) const;
};

/*******************************************************************************
 * Class Car
 ******************************************************************************/
class Car
{
private:
    std::string m_Name;
    int m_Mass;
    float m_Velocity = 0;
    float m_SurfaceArea;

    Position m_Position;
    Engine m_Engine;
    GearBox m_GearBox;
    TyreSet m_TyreSet;
    const Atmosphere* m_AtmospherePtr;

public:
    Car(const char*, const int&, const float&, const Position&, Engine&&,
        GearBox&&, TyreSet&&, const Atmosphere* const);
    Car(Car&&);
    Car(const Car&) = delete;
    ~Car();

    float calculateCurrentVelocity(const float&);
    void setVelocity(const float&);
};
