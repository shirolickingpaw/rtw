#include "helper.hpp"
#include <cmath>

arma::vec3 refract(const arma::vec3& uv, 
        const arma::vec3& n,
        double etai_over_etat) {
    auto cos_theta = std::fmin(arma::dot(-uv, n), 1.0);
    arma::vec3 r_out_prep = etai_over_etat * (uv +cos_theta*n);
    arma::vec3 r_out_parallel = -std::sqrt(std::fabs(1.0-arma::dot(r_out_prep, r_out_prep)))*n;
    return r_out_prep + r_out_parallel;
}
