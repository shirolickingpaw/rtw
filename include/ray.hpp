#ifndef RAY_HPP
#define RAY_HPP

#include <armadillo>

class ray {
    public:
        ray(); // default constructor

        // parameterized constructor
        ray(const arma::vec3& origin, const arma::vec3& direction);

        const arma::vec3& origin() const; // getter
        const arma::vec3& direction() const; // getter

        arma::vec3 at(double t) const; // compute pt on ray

    private:
        arma::vec3 orig;
        arma::vec3 dir;
};

#endif
