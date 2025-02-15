#include "ray.hpp"

ray::ray() = default;

ray::ray(const arma::vec3& origin, const arma::vec3& direction)
    : orig(origin), dir(direction) {}

const arma::vec3& ray::origin() const { return orig; }
const arma::vec3& ray::direction() const { return dir; }

arma::vec3 ray::at(double t) const {
    return orig + t * dir;
}



