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
 * @return          true if test is passed and false if not
 */
bool check_unit_test(int test_num, Vector R0, Vector R);

/*!
 *  Function for unit testing
 */
void unit_test();

#endif //SPACESHIP_UNITESTS_H
