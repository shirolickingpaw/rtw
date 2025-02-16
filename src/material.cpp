#include <cmath>
#include "material.hpp"
#include "helper.hpp"

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

dielectric::dielectric(double refraction_index)
    : refraction_index(refraction_index) {}


bool dielectric::scatter(const ray& r_in,
        const hit_record& rec,
        arma::vec3& attenuation,
        ray& scattered) const {
    attenuation = arma::vec3({1.0,1.0,1.0});
    double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

    arma::vec3 uni_direction = arma::normalise(r_in.direction());

    double cos_theta = std::fmin(arma::dot(-uni_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0-cos_theta*cos_theta);

    bool cannot_refract = ri*sin_theta>1.0;
    arma::vec3 direction;

    if (cannot_refract)
        // reflect v-2*dot(v,n)*n
        direction = uni_direction-2*arma::dot(uni_direction,rec.normal)*rec.normal;
    else
        direction = refract(uni_direction, rec.normal, ri);

    scattered = ray(rec.p, direction);
    return true;
}

double dielectric::reflectance(double cosine, double refraction_index) {
    auto r0 = (1-refraction_index)/(1+refraction_index);
    r0 = r0*r0;
    return r0 + (1-r0)*std::pow((1-cosine), 5);
}
