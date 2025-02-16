#include <armadillo>
#include <cmath>

arma::vec3 refract(const arma::vec3& uv, 
        const arma::vec3& n,
        double etai_over_etat);
        
arma::vec3 cross(const arma::vec3& u, const arma::vec3& v);
