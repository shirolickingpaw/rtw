#include "helper.hpp"
#include <cmath>

arma::vec3 random_in_unit_disk() {
    while (true) {
        auto p = arma::vec3({random_double(-1,1), random_double(-1,1), 0});
        if (arma::dot(p,p) < 1)
            return p;
    }
}

double degrees_to_radian(double degrees) {
    return degrees * arma::datum::pi/180;
}

double random_double() {
    return random_double(0, 1);
}

double random_double(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}


arma::vec3 refract(const arma::vec3& uv, 
        const arma::vec3& n,
        double etai_over_etat) {
    auto cos_theta = std::fmin(arma::dot(-uv, n), 1.0);
    arma::vec3 r_out_prep = etai_over_etat * (uv +cos_theta*n);
    arma::vec3 r_out_parallel = -std::sqrt(std::fabs(1.0-arma::dot(r_out_prep, r_out_prep)))*n;
    return r_out_prep + r_out_parallel;
}

arma::vec3 cross(const arma::vec3& u, const arma::vec3& v) {
    arma::vec3 result;
    result(0) = u(1) * v(2) - u(2) * v(1);
    result(1) = u(2) * v(0) - u(0) * v(2);
    result(2) = u(0) * v(1) - u(1) * v(0);
    return result;
}
