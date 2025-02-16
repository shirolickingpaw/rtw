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
        int samples_per_pixel = 10;
        int max_depth = 10;

        double vfov = 90; // viewing angle
        arma::vec3 lookfrom = arma::vec3({0,0,0});
        arma::vec3 lookat = arma::vec3({0,0,-1});
        arma::vec3 vup = arma::vec3({0,1,0});
        
        void render(const hittable& world);
    private:
        int image_height;
        double pixel_samples_scale; // color scale factor for a sum of samples
        arma::vec3 center;
        arma::vec3 pixel00_loc;
        arma::vec3 pixel_delta_u;
        arma::vec3 pixel_delta_v;
        arma::vec3 u,v,w;

        void initialize();
        arma::vec3 sample_square() const; 

        arma::vec3 ray_color(const ray& r, int depth, const hittable& world) const;
        ray get_ray(int i, int j) const;
};

#endif
