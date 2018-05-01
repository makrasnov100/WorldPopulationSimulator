#ifndef CONTINENT_H
#define CONTINENT_H

#include <string>
#include "sim_helper.h"

using std::string;

class Continent {
private:
    string name;
    double population;

public:
    Continent() {
        // default constructor - no parameters
    }

    Continent(string name, double population) {
        this->name = name;
        this->population = population;
    }

    void set_name(string name) {
        this->name = name;
    }

    void set_population(double population) {
        this->population = population;
    }

    string get_name() {
        return name;
    }

    double get_population() {
        return population;
    }

    void update(int day) {
        // do some cool things here...


        double d = Sim_Helper::calculate_probability(12.0, 23.0);




    }
}

#endif // CONTINENT_H
