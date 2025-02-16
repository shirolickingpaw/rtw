#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <armadillo>

#include "hittable.hpp"
#include "color.hpp"
#include "ray.hpp"

class camera {
    public:
        double aspect_ratio = 1.0; // default
        int image_width = 1024;
        
        void render(const hittable& world);
    private:
        int image_height;
        arma::vec3 center;
        arma::vec3 pixel00_loc;
        arma::vec3 pixel_delta_u;
        arma::vec3 pixel_delta_v;

        void initialize();
        arma::vec3 ray_color(const ray& r, const hittable& world) const;
};

#endif
