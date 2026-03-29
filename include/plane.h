// airport/include/plane.h

#ifndef PLANE_H
#define PLANE_H

#include "error.h"

class Plane;

// ----- PLANE -----

enum Plane_status { null, arriving, departing };

void ask_specs();

class Plane {
    public:
        Plane();
        Plane(int flt, int time, Plane_status status);
        void refuse() const;
        void land(int time) const;
        void fly(int time) const;
        void run_idle(int time) const;
        int started() const;
    private:
        int flt_num;
        int clock_start;
        Plane_status state;
};

#endif