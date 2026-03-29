// airport/airport.cpp

#include <iostream>
#include "include/plane.h"
#include "include/queue.h"
#include "include/runway.h"
#include "include/error.h"
#include "include/random.h"

class Plane;

void initialize(int &end_time, int &queue_limit, double &arrival_rate, double &departure_rate) {
    std::cout << "This program simulates an airport with only one runway.\n"
              << "One plane can land or depart in each unit of time.\n";

    std::cout << "Up to what number of planes can be waiting to land or take off at any time? ";
    std::cin >> queue_limit;

    std::cout << "How many units of time will the simulation run? ";
    std::cin >> end_time;

    bool acceptable = false;

    do {
        std::cout << "Expected number of arrivals per unit time? ";
        std::cin >> arrival_rate;

        std::cout << "Expected number of departures per unit time? ";
        std::cin >> departure_rate;

        if (arrival_rate < 0.0 || departure_rate < 0.0) {
            std::cerr << "These rates must be nonnegative.\n";
            acceptable = false;
        } else {
            acceptable = true;
            if (arrival_rate + departure_rate > 1.0)
                std::cerr << "Safety Warning: This airport will become saturated.\n";
        }

    } while (!acceptable);
}

void Runway::shut_down(int time) const {
    using namespace std;

    cout << "\nSimulation has concluded after " << time << " time units." << endl
    << "Total number of planes processed: "
    << (num_land_requests + num_takeoff_requests) << endl
    << "Total number of planes asking to land: "
    << num_land_requests << endl
    << "Total number of planes asking to take off: "
    << num_takeoff_requests << endl
    << "Total number of planes accepted for landing: "
    << num_land_accepted << endl
    << "Total number of planes accepted for takeoff: "
    << num_takeoff_accepted << endl
    << "Total number of planes refused for landing: "
    << num_land_refused << endl
    << "Total number of planes refused for takeoff: "
    << num_takeoff_refused << endl
    << "Total number of planes that landed: "
    << num_landings << endl
    << "Total number of planes that took off: "
    << num_takeoffs << endl
    << "Total number of planes left in landing queue: "
    << landing_queue.size( ) << endl
    << "Total number of planes left in takeoff queue: "
    << takeoff_queue.size( ) << endl;
    cout<< "Percentage of time runway idle: "
    << 100.0 * ((float) idle_time)/((float) time) << "%" << endl;
    cout<< "Average wait in landing queue: "
    << ((float) land_wait)/((float) num_landings) << " time units";
    cout<< endl << "Average wait in takeoff queue: "
    << ((float) takeoff_wait)/((float) num_takeoffs)
    << " time units" << endl;
    cout<< "Average observed rate of planes wanting to land: "
    << ((float) num_land_requests)/((float) time)
    << " per time unit" << endl;
    cout<< "Average observed rate of planes wanting to take off: "
    << ((float) num_takeoff_requests)/((float) time)
    << " per time unit" << endl;
}

void ask_specs() {
    int end_time, queue_limit, flight_number = 0;
    double arrival_rate, departure_rate;

    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    Random variable;

    Runway landing_runway(queue_limit);
    Runway takeoff_runway(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) {
        int number_arrivals = variable.poisson(arrival_rate);

        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);

            if (landing_runway.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate);

        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);

            if (takeoff_runway.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;

        switch (landing_runway.activity(current_time, moving_plane)) {
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                break;
            case idle:
                moving_plane.run_idle(current_time);
                break;
        }

        switch (takeoff_runway.activity(current_time, moving_plane)) {
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case land:
                break;
            case idle:
                moving_plane.run_idle(current_time);
                break;
        }
    }

    landing_runway.shut_down(end_time);
    takeoff_runway.shut_down(end_time);
}


