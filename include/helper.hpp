#include <armadillo>
#include <cmath>

arma::vec3 refract(const arma::vec3& uv, 
        const arma::vec3& n,
        double etai_over_etat);
        
arma::vec3 cross(const arma::vec3& u, const arma::vec3& v);
arma::vec3 random_in_unit_disk();
double random_double(double min, double max);
double degrees_to_radian(double degrees);
