//
// Created by grongr on 2/20/21.
//

#ifndef SPACESHIP_UNITESTS_H
#define SPACESHIP_UNITESTS_H

#include "spaceship.h"
#include <iostream>

/*!
 * Function that checks if test passed and writes if not
 * @param test_num  number of test
 * @param R0        resulting radius vector
 * @param R         correct resulting vector
 */
void check_unit_test(int test_num, Vector R0, Vector R);

#define TEST(TestNum, R_0, V_0, AVec, Builder, Mass, FuelCost, TIME, RRes)     \
    {                                                                          \
        SpaceShip sps(Builder, Mass, FuelCost, R_0, V_0, AVec);                \
                                                                               \
        sps.toggle_engine();                                                   \
        sps.move_ship(TIME);                                                   \
        check_unit_test(TestNum, sps.get_position(), RRes);                   \
    }

/*!
 *  Function for unit testing
 */
void unit_test();

#endif //SPACESHIP_UNITESTS_H
