#include <cmath>
#include "material.hpp"

lambertian::lambertian(const arma::vec3& albedo)
    : albedo(albedo) {}

bool lambertian::scatter(const ray& r_in,
        const hit_record& rec,
        arma::vec3& attenuation,
        ray& scattered) const {

    arma::vec3 random_uni_vec;
    while (true) {
        int upper_lim = 1;
        int lower_lim = -1;
        // [-1, 1)
        arma::vec3 p = lower_lim
            + (upper_lim-lower_lim)
            * arma::vec3(arma::randu<arma::vec>(3));

        auto lensq = arma::dot(p,p);
        if (1e-160 < lensq && lensq <= 1) {
            random_uni_vec = p/std::sqrt(lensq);
            break;
        }
    }
    arma::vec3 scatter_direction = rec.normal + random_uni_vec;

    if (scatter_direction[0] < 1e-8 
            && scatter_direction[1] < 1e-8
            && scatter_direction[2] < 1e-8)
        scatter_direction = rec.normal;
    
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

metal::metal(const arma::vec3& albedo, double fuzz) :
    albedo(albedo), fuzz(fuzz < 1? fuzz:1) {}

bool metal::scatter(const ray& r_in,
        const hit_record& rec,
        arma::vec3& attenuation,
        ray& scattered) const {

    arma::vec3 reflected = r_in.direction()
        - 2*arma::dot(r_in.direction() ,rec.normal)*rec.normal;

    arma::vec3 random_uni_vec;
    while (true) {
        int upper_lim = 1;
        int lower_lim = -1;
        // [-1, 1)
        arma::vec3 p = lower_lim
            + (upper_lim-lower_lim)
            * arma::vec3(arma::randu<arma::vec>(3));

        auto lensq = arma::dot(p,p);
        if (1e-160 < lensq && lensq <= 1) {
            random_uni_vec = p/std::sqrt(lensq);
            break;
        }
    }
    reflected = arma::normalise(reflected) + (fuzz*random_uni_vec);
    
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (arma::dot(scattered.direction(), rec.normal) > 0);
}

