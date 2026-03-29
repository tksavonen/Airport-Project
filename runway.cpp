// airport/runway.cpp

#include <iostream>
#include "include/plane.h"
#include "include/runway.h"
#include "include/error.h"

class Plane;

Runway::Runway(int limit) {
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
}

error_code Runway::can_land(Plane &current) {
    error_code result;

    if (landing_queue.size() < queue_limit)
        result = landing_queue.append(current);
    else
        result = overflow; 
    
    num_land_requests++;

    if (result != success)
        num_land_refused++;
    else
        num_land_accepted++;
    
        return result;
}

error_code Runway::can_depart(const Plane &current) {
    error_code result;

    if (takeoff_queue.size() < queue_limit)
        result = takeoff_queue.append(current);
    else
        result = overflow;

    num_takeoff_requests++;

    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;

    return result;
}

Runway_activity Runway::activity(int time, Plane &moving) {
    Runway_activity in_progress;
    if (!landing_queue.empty()) {
        landing_queue.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land;
        landing_queue.serve();
    }
    else if (!takeoff_queue.empty()) {
        takeoff_queue.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = takeoff;
        takeoff_queue.serve();
    }
    else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

int Runway::landing_queue_size() const {
    return landing_queue.size();
}

int Runway::takeoff_queue_size() const {
    return takeoff_queue.size();
}

