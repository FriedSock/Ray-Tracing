#include "raycast.h"
// Add any code you need here and in the corresponding header
// file.


// Constructor with parameters.
OrthographicCamera::OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size)
{
  this->centre = centre;
  this->direction = direction;
  this->direction.Normalize();
  this->up = up;
  this->up.Normalize();
  this->size = size;
  Vec3f::Cross3(this->horizontal, direction, up);
  this->horizontal.Normalize();
}


Ray OrthographicCamera::generateRay(Vec2f point)
{
    Vec3f up_component = this->up * (this->size / 2);
    Vec3f h_component = this->horizontal * (this->size / 2);   
    Vec3f top_left = (this->centre + up_component) - h_component;
    
    Vec3f right = this->horizontal;
    right *= (point.x() / this->size);
    Vec3f down = this->up;
    down *= (point.y() / this->size);
    down *= -1;
    
    Vec3f pos = top_left + right + down; 
    return Ray(this->direction, pos);
}
