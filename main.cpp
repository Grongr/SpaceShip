#include "spaceship.h"

int main() {
    EnergyFuelSystemBuilder builder(10, 1000.0, 0.1, 0.5, 10000);

    Vector R_0{0, 20, 0};
    Vector V_0{10, 0, 0};
    Vector a_vec{0, -10, 0};
    SpaceShip sps(builder, 10000, 1.0, R_0, V_0, a_vec);

    sps.move_ship(2.0);

    sps.get_position().print_vector();
    return 0;
}