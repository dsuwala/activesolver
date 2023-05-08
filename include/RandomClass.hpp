#ifndef __randomclass_hpp__
#define __randomclass_hpp__

#include<random>

class RandomClass{
    public:
        explicit RandomClass(unsigned int seed){
            setSeed(seed);
            getRandomEngine().seed(getSeed());
        }

        ~RandomClass() = default;
        
        /*! return random double from uniform distribution [0, 1)
        */
        double rand();

        /*! return random double from uniform distribution [low, high)
        */
        double randreal(double low, double high);
        
        /*! return double from uniform distribution with provided mean and variance
        */
        double randn(double mean, double variance);
        
        /*! return intiger from uniform distribution between numbers int low and int high
        */
        int randint(int low, int high);

        // getters and setters
        void setSeed(unsigned int seed){_seed = seed;}
        unsigned int getSeed() const {return _seed;}

        std::mt19937 getRandomEngine() const {return _randomEngine;}
        std::uniform_int_distribution<int> getUniformInt() const {return _rnd_uniform_int_dist;}
        std::normal_distribution<double> getNormal() const {return _rnd_normal_dist;}

    private:
        unsigned int _seed;
        std::mt19937 _randomEngine;
        std::uniform_int_distribution<int> _rnd_uniform_int_dist;
        std::normal_distribution<double> _rnd_normal_dist;
};

#endif
