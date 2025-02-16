
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <armadillo>
#include "hittable.hpp"
#include "ray.hpp"

class hit_record;

class material {
    public:
        virtual ~material() = default;
        virtual bool scatter(
                const ray& r, 
                const hit_record& rec, 
                arma::vec3& attenuation, 
                ray& scattered) const {
            return false;
        }
};

class lambertian : public material {
    public:
        lambertian(const arma::vec3& albedo);
        bool scatter(const ray& r_in,
                const hit_record& rec,
                arma::vec3& attenuation,
                ray& scattered) const override;
    private:
        arma::vec3 albedo;
};

class metal : public material {
    public:
        metal(const arma::vec3& albedo, double fuzz);
        bool scatter(const ray& r_in,
                const hit_record& rec,
                arma::vec3& attenuation,
                ray& scattered) const override;
    private:
        arma::vec3 albedo;
        double fuzz;
};

#endif
