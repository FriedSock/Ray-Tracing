#include "raycast.h"

// Add any code you need here and in the corresponding header
// file.


Sphere::Sphere()
{
  centre = Vec3f{0.0, 0.0, 0.0};
  radius = 1.0;
}



Sphere::Sphere(Vec3f centre_in, float radius_in, Vec3f color_in)
{
  this->centre = centre_in;
  this->radius = radius_in;
  this->color = color_in;
}


bool Sphere::intersect(const Ray &r, Hit &h)
{

  return false;
}
