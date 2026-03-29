// airport/plane.cpp

#include <iostream>
#include "include/plane.h"
#include "include/queue.h"
#include "include/error.h"

Plane::Plane(int flt, int time, Plane_status status) {
    flt_num = flt;
    clock_start = time;
    state = status;
    std::cout << "Plane number " << flt << " ready to ";
    if (status == arriving)
        std::cout << " land." << std::endl;
    else
        std::cout << " take off." << std::endl;
}

Plane::Plane() {
    flt_num = -1;
    clock_start = -1;
    state = null;
}

void Plane::refuse() const {
    std::cout << "Plane number " << flt_num;
    if (state == arriving)
        std::cout << " directed to another airport." << std::endl;
    else
        std::cout << " told to try to takeoff again later." << std::endl;
}

void Plane::land(int time) const {
    int wait = time - clock_start;
    std::cout << time << ": Plane number " << flt_num << " landed after "
    << wait << " time unit" << ((wait == 1)?"":"s") << " in the takeoff queue." << std::endl;
}

void Plane::fly(int time) const {
    int wait = time - clock_start;
    std::cout << time << ": Plane number " << flt_num << " took off after "
    << wait << " time unit" << ((wait == 1)?"":"s") << " in the takeoff queue." << std::endl;
}

void Plane::run_idle(int time) const {
    std::cout << time << ": Runway is idle." << std::endl;
}

int Plane::started() const {
    return clock_start;
}