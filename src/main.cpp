#include <armadillo>
#include <memory>
#include <vector>

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
    world.add(make_shared<sphere>(arma::vec3({0,0,-1}), 0.5));
    world.add(make_shared<sphere>(arma::vec3({0,-100.5,-1}), 100));
    
    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 720;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    
    cam.render(world);
}

