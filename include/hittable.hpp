#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include <armadillo>
#include "ray.hpp"
#include "interval.hpp"

class hit_record {
    public:
        arma::vec3 p;
        arma::vec3 normal;
        double t;
        bool front_face;
        
        void set_face_normal(const ray& r, const arma::vec3& outward_normal) {
            front_face = arma::dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual bool hit(const ray& r, 
                interval ray_t,
                hit_record& rec) const = 0;
};

#endif
