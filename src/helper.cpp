#include <armadillo>

#include "helper.hpp"
#include "interval.hpp"

arma::vec3 ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, arma::datum::inf), rec))
        return 0.5 * (rec.normal + arma::vec3({1,1,1}));

    // a second way to get unit vec
    arma::vec3 unit_direction = arma::normalise(r.direction());
    auto a = 0.5 * (unit_direction[1] + 1.0);
    return (1.0 - a) * arma::vec3({1.0,1.0,1.0}) + a*arma::vec3({0.5,0.7,1.0});
}
