#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "ray.hpp"

#include <armadillo>

class sphere : public hittable {
    public:
        sphere(const arma::vec3& center, double radius);
        
        bool hit(const ray& r,
                interval ray_t,
                hit_record& rec) const override;

    private:
        arma::vec3 center;
        double radius;
};

#endif
