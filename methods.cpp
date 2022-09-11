#include "classes.h"
#include <cmath>

template <typename T>
T interpolate(T x0, T y0, T x1, T y1, T x)
{
    T linear_interpolation = (y1 - y0) / (x1 - x0) * (x - x0) + y0;
    return linear_interpolation;
}

/*******************************************************************************
 * Methods of Rotable
 ******************************************************************************/
Rotable::Rotable(std::vector<float>&& value_map)
    : m_ValueMap{ std::move(value_map) }
{
    std::cout << "Create Rotable" << std::endl;
}

Rotable::Rotable(Rotable&& other)
    : m_ValueMap{ std::move(other.m_ValueMap) }
{
    std::cout << "Create Rotable w/m" << std::endl;
}

Rotable::~Rotable()
{
    std::cout << "Delete Rotable" << std::endl;
}

float Rotable::calculateOutValue(const float& in_value) const
{
    int low_point = (int)in_value % 100 * 100;
    int high_point = low_point + 100;
    return interpolate<float>(low_point,
                              m_ValueMap[(in_value + low_point) / 10],
                              high_point,
                              m_ValueMap[(in_value + high_point) / 10],
                              (float)in_value) * in_value;
}

/*******************************************************************************
 *Methods of Engine
 ******************************************************************************/
Engine::Engine(const int& rpm, const int& min_rpm, const int& max_rpm,
               std::vector<float>&& torqueMap)
    : Rotable{ std::move(torqueMap) }, m_RPM{ rpm }, m_MinRPM{ min_rpm },
      m_MaxRPM{ max_rpm }
{
    this->m_RPM = rpm >= min_rpm ? rpm : min_rpm;
    std::cout << "Create Engine" << std::endl;
}

Engine::Engine(Engine&& other)
    : Rotable{ std::move(other.m_ValueMap) }, m_RPM{ other.m_RPM },
      m_MinRPM{ other.m_MinRPM }, m_MaxRPM{ other.m_MaxRPM }
{
    std::cout << "Create Engine w/m" << std::endl;
}

Engine::~Engine()
{
    std::cout << "Delete Engine" << std::endl;
}

int Engine::getRPM() const
{
    return m_RPM;
}

/*******************************************************************************
 * Methods of Position
 ******************************************************************************/
Position::Position(const float& range)
    : m_Range{ range }
{
    std::cout << "Create Position" << std::endl;
}

Position::Position(const Position& other)
    : m_Range{ other.m_Range }
{
    std::cout << "Create Position w/c" << std::endl;
}

Position::~Position()
{
    std::cout << "Delete Position" << std::endl;
}

float Position::calculatePosition(const float& speed,
                                  const float time_delta=0.01) const
{
    return m_Range + speed * time_delta;
}

void Position::setRange(const float& range)
{
    this->m_Range = range;
}

/*******************************************************************************
* Methods of GearBox
 ******************************************************************************/
GearBox::GearBox(std::vector<float>&& ratio_map)
    : Rotable{ std::move(ratio_map) }
{
    std::cout << "Create GearBox" << std::endl;
}

GearBox::GearBox(GearBox&& other)
    :Rotable{ std::move(other.m_ValueMap) }
{
    std::cout << "Create GearBox w/m" << std::endl;
}

GearBox::~GearBox()
{
    std::cout << "Delete GearBox" << std::endl;
}

/*******************************************************************************
 * Methods of TyreSet
 ******************************************************************************/
TyreSet::TyreSet(const float& diameter)
    : m_Diameter{ diameter }
{
    std::cout << "Create TyreSet" << std::endl;
 }

TyreSet::~TyreSet()
{
    std::cout << "Delete TyreSet" << std::endl;
}

/*******************************************************************************
 * Methods of Atmosphere
 ******************************************************************************/
Atmosphere::Atmosphere(const float& air_density)
{
    this->m_AirDensity = air_density;
    std::cout << "Create Atmosphere" << std::endl;
}

Atmosphere::~Atmosphere()
{
    std::cout << "Delete Atmosphere" << std::endl;
}

float Atmosphere::calculateDrag(const float& velocity,
                                const float& surface_area) const
{
    return (m_AirDensity * pow(velocity, 3)) / 2 * surface_area;
}

/*******************************************************************************
 * Methods of Car
 ******************************************************************************/
Car::Car(const char* name, const int& mass, const float& surface_area,
         const Position& position, Engine&& engine,  GearBox&& gear_box,
         TyreSet&& tyre_set, const Atmosphere* const atmosphere_ptr)
    : m_Name{ name }, m_Mass{ mass }, m_SurfaceArea{ surface_area },
      m_Position{ position }, m_Engine{ std::move(engine) },
      m_GearBox{ std::move(gear_box) }, m_TyreSet{ std::move(tyre_set) },
      m_AtmospherePtr{ atmosphere_ptr }
{
    std::cout << "Create Car" << std::endl;
}

Car::Car(Car&& other)
    : m_Name{ std::move(other.m_Name) }, m_Mass{ other.m_Mass },
      m_Velocity{ other.m_Velocity }, m_SurfaceArea{ other.m_SurfaceArea },
      m_Position{ std::move(other.m_Position) },
      m_Engine{ std::move(other.m_Engine) },
      m_GearBox{ std::move(other.m_GearBox) },
      m_TyreSet{ std::move(other.m_TyreSet) },
      m_AtmospherePtr{ other.m_AtmospherePtr }
{
    std::cout << "Create Car w/m" << std::endl;
}

Car::~Car()
{
    std::cout << "Delete Car" << std::endl;
}

float Car::calculateCurrentVelocity(const float& time_delta)
{
    float engine_power = m_Engine.calculateOutValue(m_Engine.getRPM());
    float drag_power =
        m_Velocity * m_AtmospherePtr->calculateDrag(m_Velocity, m_SurfaceArea);
    float effective_power = engine_power - drag_power;
    if (effective_power < 0)
    {
        return m_Velocity;
    }
    else
    {
        m_Velocity = sqrt(2 * effective_power * time_delta
                            / m_Mass + pow(m_Velocity, 2));
        return m_Velocity;
    }
 }

void Car::setVelocity(const float& velocity)
{
    this->m_Velocity = velocity;
}
