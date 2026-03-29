// airport/include/RANDOM.H

#ifndef RANDOM_H
#define RANDOM_H

class Random {
public:
   Random(bool pseudo = true);
   int random_integer(int low, int high);
   double random_real();
   int poisson(double mean);
private:
   int reseed(); 
   int seed, multiplier, add_on;
};

#endif
