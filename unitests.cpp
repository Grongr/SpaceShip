//
// Created by grongr on 2/20/21.
//

#include "unitests.h"

void check_unit_test(int test_num, Vector R0, Vector R) {
    if (R0 != R) {
        std::cout << "Test number " << test_num << "not passed!" << std::endl;
    }
}
void unit_test() {
    {
        EnergyFuelSystemBuilder builder(10, 1000.0, 1, 1, 10000);
        TEST(1, Vector(0, 20, 0), Vector(10, 0, 0), Vector(0, -10, 0),
             builder, 10000, 1.0, 2.0, Vector(20, 0, 0))
    }

    {
        EnergyFuelSystemBuilder builder(10, 0.2, 1, 1, 100000);
        TEST(2, Vector(0, 20, 0), Vector(10, 0, 0), Vector(0, -10, 0),
             builder, 10000, 1.0, 4.0, Vector(40, 40, 0))
    }
}