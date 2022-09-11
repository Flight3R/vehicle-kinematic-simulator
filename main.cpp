#include "classes.h"

int main()
{
    std::vector<int> torqueMap =
        { 130, 170, 190, 205, 220, 245, 258, 250, 240, 240,
          240, 245, 250, 250, 240, 240, 240, 230, 220, 218,
          216, 210, 202, 195, 195, 185, 180, 178, 170, 165,
          160, 140 };

    std::vector<float> testTorqueMap =
        { 57.7, 59.95, 62.2, 64.45, 66.7, 68.95, 71.2, 73.45, 75.7, 77.95,
          80.2, 82.45, 84.7, 86.95, 89.2, 91.45, 93.7, 95.95, 98.2, 100.45,
          102.7, 104.95, 107.2, 109.45, 111.7, 113.95, 116.2, 118.45, 120.7,
          122.95, 125.2, 127.45, 129.7, 131.95, 134.2, 136.45, 138.7, 140.95,
          143.2, 145.45, 147.7, 149.95, 152.2, 154.45, 156.7, 158.95, 161.2,
          163.45, 165.7, 167.95, 170.2, 172.45, 174.7, 176.95, 179.2, 181.45,
          183.7, 185.95, 188.2, 190.45 };

    std::vector<float> testRatioMap = {};

    Position testPosition{ 0.0 };
    Engine testEngine{ 1200, 1000, 6000, std::move(testTorqueMap) };
    GearBox testGearBox{ std::move(testRatioMap) };
    TyreSet testTyreSet{ 0.5 };
    Atmosphere testAtm{ 1 };
    Car testCar{ "test_car", 2400, 4, testPosition, std::move(testEngine),
                 std::move(testGearBox), std::move(testTyreSet), &testAtm };

    std::cout << "--- end of main ---" << std::endl;
    return 0;
}