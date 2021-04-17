//
// Created by grongr on 2/11/21.
//

#ifndef SPACESHIP_SPACESHIP_H
#define SPACESHIP_SPACESHIP_H

#define DEBUG

#include <vector>
#include <string>
#include <exception>
#include <cmath>

//-----------------------------------------------------------------------------------------------------------//
/*!
 * Error which is thrown when count of params of EFS builder is not 5
 */
class EFSParamCountError : std::exception {
public:

    /*!
     * Default constructor to this error type
     * @param error  string which says what is an error
     */
    explicit EFSParamCountError(std::string error) : error{std::move(error)} {}

    const char* what() const noexcept final { return error.c_str(); }

private:
    std::string error;
};

class SpaceShipBCountError : std::exception {
public:

    /*!
     * Default constructor to this error type
     * @param error  some info about this error
     */
    explicit SpaceShipBCountError(std::string error) : error{std::move(error)} {}

    const char* what() const noexcept final { return error.c_str(); }
private:
    std::string error;
};

//-----------------------------------------------------------------------------------------------------------//
/*!
 * Geometric representation of a vector in 3D space
 */
class Vector {
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

    /*!
     * Operator !=
     * @param r
     * @return true if this != r
     */
    bool operator!= (Vector const &r) const;

    /*!
     * How to integrate one vector into another
     * @param p
     * @return result vector
     */
    Vector& operator= (Vector const &p) = default;

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
    explicit EnergyFuelSystem(int size_of_bat_arr, double battery_energy, double fu,
                              double fQ, double fmv) {
       bat.resize(size_of_bat_arr);

       for (int i = 0; i < size_of_bat_arr; ++i)
           bat[i].set_energy(battery_energy);
       this->full_energy = size_of_bat_arr * battery_energy;

       this->tank.set_params(fmv, fmv, fu, fQ);
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

    ~EnergyFuelSystem() = default;

private:
    double full_energy{0};
    std::vector<Battery> bat;
    FuelTank tank{0, 0, 0, 0};
};
//-----------------------------------------------------------------------------------------------------------//
/*!
 * This struct with it's constructor should be used to create any EnergyFuelSystem
 */
class EnergyFuelSystemBuilder {
protected:
    int    size_of_bat_arr;              //! Count of batteries in Energy system
    double battery_energy;               //! Energy amount in one battery
    double fu;                           //! Energy cost to use fQ amount of fuel in fuel system
    double fQ;                           //! Max amount of fuel to use in one time in fuel system
    double fmv;                          //! Value of fuel in fuel system
    int    count_of_setted_params;       //! If not enough params setted efs can't be made

public:
    /*!
     * Default constructor for this builder
     */
    EnergyFuelSystemBuilder() :
            size_of_bat_arr{0}, battery_energy{0}, fu{0},
            fQ{0}, fmv{0}, count_of_setted_params{0} {}

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
            fu{fu}, fQ{fQ}, fmv{fmv}, count_of_setted_params{5} {}
    /*!
    * This group of functions is made to set the params of builder in comfort way
    */
    void set_size_of_bat_arr(int size_) { this->size_of_bat_arr = size_; count_of_setted_params++; }
    void set_bat_energy(double energy_) { this->battery_energy = energy_; count_of_setted_params++; }
    void set_fmv(double fmv_)           { this->fmv = fmv_; count_of_setted_params++; }
    void set_fu(double fu_)             { this->fu = fu_; count_of_setted_params++; }
    void set_fQ(double fQ_)             { this->fQ = fQ_; count_of_setted_params++; }

    /*!
     * This method should be used to make Energy Fuel System
     * @return pointer to prepared to work energy fuel system
     */
    EnergyFuelSystem* make_efs() const {
        if (count_of_setted_params != 5)
            throw EFSParamCountError("Count of params of Energy fuel system is not 5");
        auto efs = new EnergyFuelSystem(size_of_bat_arr, battery_energy, fu, fQ, fmv);
        return efs;
    }

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
    SpaceShip(EnergyFuelSystemBuilder const &builder, double mass, double fuel_cost,
              Vector R, Vector V, Vector a_vec)
            : mass{mass}, R{R}, efs(*builder.make_efs()), fuel_cost{fuel_cost}, V{V}, AVec{a_vec} {}

    /*!
     * Constructor without initialization of Radius
     * @param mass
     * @param fuel
     */
    SpaceShip(EnergyFuelSystemBuilder const& builder, double mass, double fuel_cost):
            mass{mass}, R{0, 0, 0},
            V{0, 0, 0},
            fuel_cost{fuel_cost},
            efs(*builder.make_efs()) {}

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
//-----------------------------------------------------------------------------------------------------------//
class SpaceShipBuilder {
public:
    /*!
     * Constructor with no params
     */
    SpaceShipBuilder() : R{0, 0, 0}, V{0, 0, 0}, AVec{0, 0, 0},
                         mass{1}, fuel_cost{0}, is_engine_active{false}, count_of_params{0} {}

    /*!
     * Constructor with all the params
     * @param R
     * @param V
     * @param AVec
     * @param mass
     * @param fuel_cost
     * @param is_engine_active
     */
    SpaceShipBuilder(Vector const& R, Vector const& V, Vector const& AVec,
                     double mass, double fuel_cost, bool is_engine_active)
        : R{R}, V{V}, AVec{AVec}, mass{mass}, fuel_cost{mass},
          is_engine_active{is_engine_active}, count_of_params{5} {}

    /*
     *  List of functions which could be used to set params of spaceship
     */
    void set_fuel_cost(double fuel_cost) { this->fuel_cost = fuel_cost; ++count_of_params; }
    void set_is_engine_active(bool b)    { this->is_engine_active = b; ++count_of_params; }
    void set_AVec(Vector const& AVec)    { this->AVec = AVec; ++count_of_params; }
    void set_R(Vector const& R)          { this->R = R; ++count_of_params; }
    void set_V(Vector const& V)          { this->V = V; ++count_of_params; }
    void set_mass(double mass)           { this->mass = mass; ++count_of_params; }

    SpaceShip* make_spaceship(EnergyFuelSystemBuilder const& efs) {
        if (count_of_params != 6)
            throw SpaceShipBCountError("Count of params in spaceship builder is not 6");
        auto sps = new SpaceShip(efs, mass, fuel_cost, R, V, AVec);
        return sps;
    }

protected:
    Vector R{}, V{}, AVec{};
    double mass, fuel_cost;
    bool is_engine_active;
    int count_of_params{0};
};
//TODO write builder for a SpaceShip

#endif //SPACESHIP_SPACESHIP_H
