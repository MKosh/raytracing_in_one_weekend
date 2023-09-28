#pragma once

#include "interval.h"
#include "ray.h"
#include "vec3.h"

class hit_record {
public:
  point3 p;
  vec3<double> normal;
  double t;
  bool front_face;

  auto set_face_normal(const ray& r, const vec3<double>& outward_normal) -> void {
    // Sets the hit record normal vector.
    // NOTE: the parameter 'outward_normal' is assumed to have unit length.
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
public:
  virtual ~hittable() = default;

  virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

private:
  
};

