#include <armadillo>
#include "ray.hpp"
#include "hittable.hpp"

arma::vec3 ray_color(const ray& r, const hittable& world);