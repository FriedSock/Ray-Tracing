#include "raycast.h"

// Constructor for a group of n objects.
Group::Group(int n) {

  this->_object = new Object3D*[n];
  this->_count  = n;
  for(int i = 0; i < n; ++i) {
    this->_object[i] = NULL;
  }
}

// Destructor.
Group::~Group() {

  if (this->_object == NULL) {
    return;
  }

  for (int i = 0; i < this->_count; i++) {
    if (this->_object[i] != NULL) {
      delete this->_object[i];
    }
  }
  delete[] this->_object;
}

// Insert an object into the array.
void Group::addObject(int index, Object3D *obj) {
    if (index > this->_count) {
        //TODO error message
        exit(1);
    }

    this->_object[index] = obj;
}

bool Group::intersect(const Ray &r, Hit &h)
{
  bool result = false;
  for (int i = 0; i < this->_count; i++) {
    result = this->_object[i]->intersect(r, h) || result;
  }
  return result;
}
