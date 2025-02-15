#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include <memory>
#include <vector>

#include "hittable.hpp"
#include "interval.hpp"
#include "ray.hpp"

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list();
        hittable_list(shared_ptr<hittable> object);

        void clear();

        void add(shared_ptr<hittable> object);
        bool hit(const ray& r,
                interval ray_t,
                hit_record& rec) const override;
};

#endif
