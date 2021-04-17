//
// Created by grongr on 2/20/21.
//

#include "unitests.h"

#define TEST(TestNum, R_0, V_0, AVec, Builder, Mass, FuelCost, TIME, RRes)     \
    {                                                                          \
        SpaceShip sps(Builder, Mass, FuelCost, R_0, V_0, AVec);                \
                                                                               \
        sps.toggle_engine();                                                   \
        sps.move_ship(TIME);                                                   \
        check_unit_test(TestNum, sps.get_position(), RRes);                    \
    }

bool check_unit_test(int test_num, Vector R0, Vector R) {
    if (R0 != R) {
        std::cout << "Test number " << test_num << " not passed!" << std::endl;

        std::cout << "The vector that we got" << std::endl;
        R0.print_vector();
        std::cout << "The vector we needed" << std::endl;
        R.print_vector();

        return false;
    } else {
        std::cout << "Test number " << test_num << " passed correctly :)" << std::endl;
        return true;
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
             builder, 10000, 1.0, 4.0, Vector(40, -40, 0))
    }

    {
        EnergyFuelSystemBuilder builder(10, 10000, 1, 1, 10000);
        TEST(3, Vector(0, 20, 0), Vector(10, 0, 0), Vector(0, -10, 0),
             builder, 10000, 10000, 4.0, Vector(40, -15, 0))
    }
}

#undef TEST