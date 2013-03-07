#include "raycast.h"

// Add any code you need here and in the corresponding header
// file.


Sphere::Sphere()
{
  centre = Vec3f(0.0, 0.0, 0.0);
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
  const Vec3f d = r.getDirection();
  const Vec3f deltaP = r.getOrigin() - this->centre;

  float d_dot_deltaP = d.Dot3(deltaP);
  d_dot_deltaP *= d_dot_deltaP;

  float deltaP_mag_squared = deltaP.magnitudeSquared();
  float r_squared = this->radius * this->radius;
  float discriminant = d_dot_deltaP - deltaP_mag_squared + r_squared;
  if (discriminant < 0)
      return false;

  discriminant = sqrt(discriminant);

  Vec3f neg_d = d * -1;
  float neg_d_dot = neg_d.Dot3(deltaP);
  
  float u1 = neg_d_dot + discriminant;
  float u2 = neg_d_dot - discriminant;

  float closest = (u1 < u2)? u1 : u2;
  
  if (closest < h.getT())
      h.set(closest, this->color);

  return true;
}
