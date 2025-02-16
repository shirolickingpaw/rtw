#include <armadillo>
#include <memory>
#include <vector>

#include "material.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

using std::make_shared;
using std::shared_ptr;

int main() {

    // world settings
    hittable_list world;
    auto material_ground = make_shared<lambertian>(arma::vec3({0.8, 0.8, 0.0}));
    auto material_center = make_shared<lambertian>(arma::vec3({0.1, 0.2, 0.5}));
    auto material_left   = make_shared<metal>(arma::vec3({0.8, 0.8, 0.8}), 0.3);
    auto material_right  = make_shared<metal>(arma::vec3({0.8, 0.6, 0.2}), 1.0);

    world.add(make_shared<sphere>(arma::vec3({ 0.0, -100.5, -1.0}), 100.0, material_ground));
    world.add(make_shared<sphere>(arma::vec3({ 0.0,    0.0, -1.2}),   0.5, material_center));
    world.add(make_shared<sphere>(arma::vec3({-1.0,    0.0, -1.0}),   0.5, material_left));
    world.add(make_shared<sphere>(arma::vec3({ 1.0,    0.0, -1.0}),   0.5, material_right));
    
    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 720;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    
    cam.render(world);
}

