#include "hittable.hpp"
#include "sphere.hpp"
#include <cmath>

sphere::sphere(const arma::vec3& center, double radius) :
    center(center), radius(std::fmax(0, radius)) {}

bool sphere::hit(const ray& r,
        interval ray_t,
        hit_record& rec) const {

    arma::vec3 oc = center - r.origin();
    auto a = arma::dot(r.direction(), r.direction());
    auto h = arma::dot(r.direction(), oc);
    auto c = arma::dot(oc, oc) - radius*radius;

    auto discriminant = h*h - a*c;
    if (discriminant < 0) {
        return false;
    }

    auto sqrtd = std::sqrt(discriminant);

    auto root = (h - sqrtd)/a;
    if (!ray_t.surrounds(root)) {
        root = (h + sqrtd)/a;
        if (!ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    arma::vec3 outward_normal = (rec.p - center)/radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}
