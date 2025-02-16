#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <material.hpp>
#include "hittable.hpp"
#include "ray.hpp"

#include <armadillo>
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class sphere : public hittable {
    public:
        sphere(const arma::vec3& center, 
                double radius,
                shared_ptr<material> mat);
        
        bool hit(const ray& r,
                interval ray_t,
                hit_record& rec) const override;

    private:
        arma::vec3 center;
        double radius;
        shared_ptr<material> mat;
};

#endif
