//
// Created by grongr on 2/11/21.
//

#ifndef SPACESHIP_SPACESHIP_H
#define SPACESHIP_SPACESHIP_H

#define DEBUG

#include <cmath>

//-----------------------------------------------------------------------------------------------------------//
/*!
 * Geometric representation of a vector in 3D space
 */
class Vector
{
public:
    /*!
     * Default constructor.
     * Params become zeroes :)
     */
    Vector() : x{0}, y{0}, z{0} { }

    /*!
     * Constructor which could initialize all coordinates
     * @param x
     * @param y
     * @param z
     */
    Vector(double x, double y, double z) : x{x}, y{y}, z{z} { }

    /*!
     * @return the length of a vector
     */
    double length() const { return sqrt(x * x + y * y + z * z); }

    /*!
     * This is how Vectors are summed. Yeah
     * I wish, there is the word like "summed" in English language
     * @param p
     * @return
     */
    Vector operator+ (Vector const& r) const;

    /*!
     * You know, that is vector that is multiplied on a real number...
     * @param value
     * @return
     */
    Vector operator* (double value) const;

    bool operator!= (Vector const &r) const;

    /*!
     * How to integrate one vector into another
     * @param p
     * @return result vector
     */
    Vector& operator= (Vector p);

#ifdef DEBUG

    /*!
     * Simply out x, y, z
     */
    void print_vector() const;

#endif // DEBUG

protected:
    /*!
     * Coordinates of a point in space
     */
    double x, y, z;
};
//-----------------------------------------------------------------------------------------------------------//
/*!
 * A class that structure energy conversions
 */
class Battery {
public:

    /*!
     * Default constructor for Battery.
     * Params of this class become zero :)
     */
    Battery() : contain_energy{0}, max_energy{0} { }

    /*!
     * Constructor with initializes maximum of containing energy
     * @param max_energy
     */
    explicit Battery(double max_energy) : contain_energy{max_energy}, max_energy{max_energy} { }

    /*!
     * Changes containing amount of energy
     * I NEED POWER, MORE POWER
     * @param energy
     * @return the amount of energy it used
     */
    double use_battery(double energy);

    /*!
     * @return how many energy is in a battery
     */
    double how_many_energy() const { return contain_energy; }

    /*!
     * Sets maximum and containing energy
     * @param mv maximum energy
     */
    void set_energy(double mv) {
        this->contain_energy = this->max_energy = mv;
    }

    ~Battery() = default;

private:
    /*!
     * Energy in the moment of use and maximum containing energy
     * @param contain_energy    in that moment
     * @param max_energy        maximum of possible energy
     */
    double contain_energy;
    double max_energy;
};
//-----------------------------------------------------------------------------------------------------------//
/*!
 * A class that uses energy to give fuel on a side
 */
class FuelTank {
public:

    /*!
     * Minimum needed params
     * @param u how many energy you need to receive Q of fuel
     * @param Q max amount of fuel you may use in one time
     */
    FuelTank(double u, double Q) : u{u}, Q{Q}, contain_v{0}, max_v{0} { }

    /*!
     * Now you know onw more param
     * @param u  how many energy you need to receive Q of fuel
     * @param Q  max amount of fuel you may use in one time
     * @param mv max value of fuel in tank
     */
    FuelTank(double u, double Q, double mv) : u{u}, Q{Q}, max_v{mv}, contain_v{mv} { }

    /*!
     * Constructor with all the params
     * @param u  how many energy you need to receive Q of fuel
     * @param Q  max amount of fuel you may use in one time
     * @param mv max value of fuel in tank
     * @param cv containing value of fuel
     */
    FuelTank(double u, double Q, double mv, double cv) : u{u}, Q{Q}, max_v{mv}, contain_v{cv} {}

    /*!
     * Gets some fuel from tank and counts amount of energy to do this
     * @param f amount of fuel we need to get
     * @return  amount to energy we have to lose
     */
    double get_some_fuel(double f);

    /*!
     * How much is it cost to give that amount of fuel
     * @param f amount of fuel
     * @return  energy to use
     */
    double energy_cost(double f) const;

    /*!
     * Sets params of class exemplar
     * @param cv
     * @param mv
     * @param fu
     * @param fQ
     */
    void set_params(double cv, double mv, double fu, double fQ) {
        this->contain_v = cv;
        this->max_v     = mv;
        this->u         = fu;
        this->Q         = fQ;
    }

    /*!
     * If you wanna know how many fuel you have
     * @return contain_v
     */
    double get_fuel() const { return contain_v; }

    /*!
     * It checks how many fuel we can give with <energy> amount of energy
     * @param energy
     * @return
     */
    double max_amount_of_fuel_to_give(double energy) const;

    ~FuelTank() = default;

private:
    /*!
     * @param contain_v containing value of fuel
     * @param u         how many energy you need to receive Q of fuel
     * @param max_v     max value of fuel in tank
     * @param Q         max amount of fuel you may use in one time
     */
    double contain_v;
    double max_v;
    double u, Q;
};
//-----------------------------------------------------------------------------------------------------------//
/*!
 * This struct with it's constructor should be used to create any EnergyFuelSystem
 */
struct EnergyFuelSystemBuilder {
    int size_of_bat_arr;              //! Count of batteries in Energy system
    double battery_energy;               //! Energy amount in one battery
    double fu;                           //! Energy cost to use fQ amount of fuel in fuel system
    double fQ;                           //! Max amount of fuel to use in one time in fuel system
    double fmv;                          //! Value of fuel in fuel system

    /*!
     * Constructor of builder.
     * Initialises all the params of it
     * @param size_of_bat_arr
     * @param battery_energy
     * @param fu
     * @param fQ
     * @param fmv
     */
    EnergyFuelSystemBuilder(int size_of_bat_arr, double battery_energy,
                            double fu, double fQ, double fmv) :
            size_of_bat_arr{size_of_bat_arr}, battery_energy{battery_energy},
            fu{fu}, fQ{fQ}, fmv{fmv} {}
};
//-----------------------------------------------------------------------------------------------------------//
/*!
 * It is system that contains an integer number of batteries and a fuel tank
 */
class EnergyFuelSystem {
public:

    /*!
     * This constructor could be used to create engine system
     * It makes a lot of identical batteries and one full of
     * fuel FuelTank
     * @param size_of_bat_arr
     * @param battery_energy
     * @param fu
     * @param fQ
     * @param fmv
     */
    explicit EnergyFuelSystem(EnergyFuelSystemBuilder builder) {
       bat = new Battery[builder.size_of_bat_arr];
       this->batteries_count = builder.size_of_bat_arr;

       for (int i = 0; i < builder.size_of_bat_arr; ++i)
           bat[i].set_energy(builder.battery_energy);
       this->full_energy = builder.size_of_bat_arr * builder.battery_energy;

       this->tank.set_params(builder.fmv, builder.fmv, builder.fu, builder.fQ);
    }

    /*!
     * Checks if we have enough energy to give that amount of fuel;
     * @return true if we have enough resources; false if not
     */
    bool have_enough_resources(double fuel);

    /*!
     * This func makes all the work
     * It gives maximum of possible fuel
     * @param  fuel
     * @return total amount of used fuel
     */
    double use_some_fuel(double fuel);

    double get_fuel() const { return tank.get_fuel(); }

    ~EnergyFuelSystem() {
        delete [] this->bat;
        full_energy = 0;
    }

private:
    double full_energy{0};
    Battery *bat;
    int batteries_count{0};
    FuelTank tank{0, 0, 0, 0};
};
//-----------------------------------------------------------------------------------------------------------//
class SpaceShip {
public:
    /*!
     * Constructor with some initialization
     * @param builder   - special builder for fuel system
     * @param mass      - mass of spaceship
     * @param fuel_cost - how many fuel it takes to move
     * @param R         - start location
     * @param V         - start velocity
     */
    SpaceShip(EnergyFuelSystemBuilder builder, double mass, double fuel_cost,
              Vector R, Vector V, Vector a_vec)
            : mass{mass}, R{R}, efs(builder), fuel_cost{fuel_cost}, V{V}, AVec{a_vec} {}

    /*!
     * Constructor without initialization of Radius
     * @param mass
     * @param fuel
     */
    SpaceShip(EnergyFuelSystemBuilder builder, double mass, double fuel_cost):
            mass{mass}, R{0, 0, 0},
            V{0, 0, 0},
            fuel_cost{fuel_cost},
            efs(builder) {}

    /*!
     * Changed direction of acceleration to new_dir
     * @param new_dir
     */
    void set_accel_direction(Vector new_dir) { this->AVec = new_dir; }

    /*!
     * Changing radius vector of space ship while it is moving for <time>
     * @param time
     */
    void move_ship(double time);

    /*!
     * Toggles engine active or not.
     * @return value of <is_engine_active> after toggling
     */
    bool toggle_engine();

    /*!
     * Function to see how many fuel we have
     * @return value of a <fuel> variable
     */
    double get_fuel() const { return efs.get_fuel(); }

    /*!
     * Checks if engine is active or not
     * @return value of <is_engine_active> variable
     */
    bool is_engine_active_or_not() const { return is_engine_active; }

    /*!
     * If you wanna know where the ship is.
     * @return a position of the ship
     */
    Vector get_position() const { return R; }

    /*!
     * If you wanna know the velocity of the ship
     * @return a velocity of the ship
     */
    Vector get_velocity() const { return V; }

private:
    /*!
     * @param R                 radius vector of the ship
     * @param V                 velocity
     * @param AVec              acceleration
     * @param fuel              how much fuel it has
     * @param fuel_cost         how much fuel it eats in a time
     * @param bat               batteries of this ship
     * @param is_engine_active  is engine active??? hmmmm, Иногда я думаю, что моя гениальность создает гравитацию
     */
    Vector R{}, V{}, AVec{1, 0, 0};
    double mass, fuel_cost;
    bool is_engine_active{false};
    EnergyFuelSystem efs;
};

#endif //SPACESHIP_SPACESHIP_H
