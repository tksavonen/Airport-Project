// airport/include/runway.h

#ifndef RUNWAY_H
#define RUNWAY_H

#include "plane.h"
#include "queue.h"

enum Runway_activity { idle, land, takeoff };

Runway_activity activity_land_only(int time, Plane &moving);
Runway_activity activity_takeoff_only(int time, Plane &moving);

class Runway {
    public:
        Runway(int limit);
        error_code can_land(Plane &current);
        error_code can_depart(const Plane &current);
        Runway_activity activity(int time, Plane &moving);
        void shut_down(int time) const;
    private:
        Extended_queue landing_queue;
        Extended_queue takeoff_queue;
        int landing_queue_size() const;
        int takeoff_queue_size() const;
        int queue_limit;
        int num_land_requests; 
        int num_takeoff_requests; 
        int num_landings; 
        int num_takeoffs; 
        int num_land_accepted; 
        int num_takeoff_accepted; 
        int num_land_refused; 
        int num_takeoff_refused; 
        int land_wait; 
        int takeoff_wait; 
        int idle_time; 
};

#endif