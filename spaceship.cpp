//
// Created by grongr on 2/11/21.
//

#include "spaceship.h"

//-----------------------------------------------------------------------------------------------------------//
Vector Vector::operator+(Vector v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}

Vector Vector::operator*(double value) {
    this->x *= value;
    this->y *= value;
    this->z *= value;
}

//-----------------------------------------------------------------------------------------------------------//
void SpaceShip::move_ship(double time) {
    double needed_fuel = time * fuel_cost;

    double used_fuel = this->efs.use_some_fuel(needed_fuel);

    time = used_fuel / this->fuel_cost;

    R = R + V * time + AVec * (time * time / 2.0);
}

bool SpaceShip::toggle_engine() {
    is_engine_active = !is_engine_active;
    return is_engine_active;
}

//-----------------------------------------------------------------------------------------------------------//
double Battery::use_battery(double energy) {
    if (energy <= 0)
        return 0;

    if (energy >= this->contain_energy) {
        this->contain_energy = 0;
        return energy;
    }
    this->contain_energy -= energy;
    return energy;
}

//-----------------------------------------------------------------------------------------------------------//
double FuelTank::get_some_fuel(double f) {
    if (f == 0 || contain_v == 0)                       // We cannot give that amount of fuel
        return 0;

    f = fmin(f, contain_v);                             // Maximum which we can give

    if (f < Q) {                                        // We only need one Q to give all we can or need
        contain_v -= f;
        return u;
    } else if ((int)(f / Q) == f / Q) {                 // If f contains an integer number of Q
        contain_v -= f;
        return (u * (int)(f / Q));
    } else {                                            // If not integer number of Q'es
        int count = (int) (f / Q) + 1;
        if (count * Q > contain_v) {                        // 1. When we need more then can give
            contain_v = 0;
            return u * count;
        } else {                                            // 2. When all is ok and none will be blamed
            contain_v -= count * Q;                         //    for greed
            return u * count;
        }
    }
}

double FuelTank::energy_cost(double f) const {
    if (f == 0 || contain_v == 0)                       // We cannot give that amount of fuel
        return 0;

    f = fmin(f, contain_v);                             // Maximum which we can give

    if (f < Q) {                                        // We only need one Q to give all we can or need
        return u;
    } else if ((int)(f / Q) == f / Q) {                 // If f contains an integer number of Q
        return (u * (int)(f / Q));
    } else {                                            // If not integer number of Q'es
        int count = (int) (f / Q) + 1;
        return u * count;
    }
}

double FuelTank::max_amount_of_fuel_to_give(double energy) const {
    int count = (int) (energy / this->u);               // How many times we can give Q amount of fuel

    return fmax(count * Q, this->contain_v);
}
//-----------------------------------------------------------------------------------------------------------//
bool EnergyFuelSystem::have_enough_resources(double fuel) {
    double needed_energy = this->tank.energy_cost(fuel);

    if (needed_energy > this->full_energy)
        return false;

    if (fuel > this->get_fuel())
        return false;

    return true;
}

double EnergyFuelSystem::use_some_fuel(double fuel) {
    fuel = fmin(this->tank.max_amount_of_fuel_to_give(this->full_energy), fuel);

    double used_energy = this->tank.get_some_fuel(fuel);

    this->full_energy -= used_energy;

    int i = this->batteries_count - 1;

    while (used_energy > 0) {
        used_energy -= bat[i].use_battery(used_energy);
        --i;
    }
    return fuel;
}
//-----------------------------------------------------------------------------------------------------------//
